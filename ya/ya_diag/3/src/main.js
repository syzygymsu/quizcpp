// Не забудьте перед отправкой изменить в module.exports = function main(game, start) {
// Не деструктурируйте game, ваше решение не будет проходить тесты.

function getKey(point) {
    return point.x + "|" + point.y;
}

function wait_new_point(point, game) {
    return game.state(point.x, point.y).then((res) => {
        return {state: res, point: point};
    });
}

async function helper(game, start) {
    // const queue = [];
    const waiter = [];
    const visited = {};
    waiter.push(wait_new_point(start, game));
    // queue.push(start);
    while (waiter.length !== 0) {
        const cur_task = waiter.shift();
        const cur_res = await cur_task;
        const cur_point = cur_res.point;
        if (visited[getKey(cur_point)]) {
            continue;
        }
        const res = cur_res.state;
        if (res.finish === true) {
            return cur_point;
        }
        visited[getKey(cur_point)] = true;
        if (res.top) {
            const cand_point = {x: cur_point.x, y: cur_point.y - 1};
            if (!visited[getKey(cand_point)]) {
                const up_prom = game.up(cur_point.x, cur_point.y).then(() => wait_new_point(cand_point, game));
                waiter.push(up_prom);
            }
        }
        if (res.bottom) {
            const cand_point = {x: cur_point.x, y: cur_point.y + 1};
            if (!visited[getKey(cand_point)]) {
                const down_prom = game.down(cur_point.x, cur_point.y).then(() => wait_new_point(cand_point, game));
                waiter.push(down_prom);
            }
        }
        if (res.left) {
            const cand_point = {x: cur_point.x - 1, y: cur_point.y};
            if (!visited[getKey(cand_point)]) {
                const left_prom = game.left(cur_point.x, cur_point.y).then(() => wait_new_point(cand_point, game));
                waiter.push(left_prom);
            }
        }
        if (res.right) {
            const cand_point = {x: cur_point.x + 1, y: cur_point.y};
            if (!visited[getKey(cand_point)]) {
                const right_prom = game.right(cur_point.x, cur_point.y).then(() => wait_new_point(cand_point, game));
                waiter.push(right_prom);
            }
        }
    }
    return start;
}


// module.exports = function main(game, start) {
//     return helper(game, start);
// }

export default function main(game, start) {
    return helper(game, start);
}
