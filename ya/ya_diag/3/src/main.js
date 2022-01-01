// Не забудьте перед отправкой изменить в module.exports = function main(game, start) {
// Не деструктурируйте game, ваше решение не будет проходить тесты.

function getKey(point) {
    return point.x + "|" + point.y;
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function helper(game, start) {
    const queue = [];
    const visited = {};
    const st = await game.state(start.x, start.y);
    queue.push({point: start, state: st});
    while (true) {
        if (queue.length === 0) {
            await sleep(200);
            continue;
        }
        const cur_res = queue.shift();
        const cur_point = cur_res.point;
        const res = cur_res.state;
        if (res.finish === true) {
            return cur_point;
        }
        const key_cur = getKey(cur_point);
        if (visited[key_cur]) {
            continue;
        } else {
            visited[key_cur] = true;
        }
        if (res.top) {
            const cand_point = {x: cur_point.x, y: cur_point.y - 1};
            if (!visited[getKey(cand_point)]) {
                game.up(cur_point.x, cur_point.y)
                    .then(() => game.state(cand_point.x, cand_point.y))
                    .then((st) => queue.push({point: cand_point, state: st}));
            }
        }
        if (res.bottom) {
            const cand_point = {x: cur_point.x, y: cur_point.y + 1};
            if (!visited[getKey(cand_point)]) {
                game.down(cur_point.x, cur_point.y)
                    .then(() => game.state(cand_point.x, cand_point.y))
                    .then((st) => queue.push({point: cand_point, state: st}));
            }
        }
        if (res.left) {
            const cand_point = {x: cur_point.x - 1, y: cur_point.y};
            if (!visited[getKey(cand_point)]) {
                game.left(cur_point.x, cur_point.y)
                    .then(() => game.state(cand_point.x, cand_point.y))
                    .then((st) => queue.push({point: cand_point, state: st}));
            }
        }
        if (res.right) {
            const cand_point = {x: cur_point.x + 1, y: cur_point.y};
            if (!visited[getKey(cand_point)]) {
                game.right(cur_point.x, cur_point.y)
                    .then(() => game.state(cand_point.x, cand_point.y))
                    .then((st) => queue.push({point: cand_point, state: st}));
            }
        }
    }
}

// module.exports = function main(game, start) {
//     return helper(game, start);
// }

export default function main(game, start) {
    return helper(game, start);
}
