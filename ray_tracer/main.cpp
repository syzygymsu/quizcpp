#include <cmath>
#include <cstdio>
#include <vector>

double drand48();

constexpr const double H = 1003;

struct Vec3 {
    double x, y, z;

    explicit Vec3(double a = 0, double b = 0, double c = 0) : x{a}, y{b}, z{c} {}

    [[nodiscard]] Vec3 sum(Vec3 b) const { return Vec3(x + b.x, y + b.y, z + b.z); }

    [[nodiscard]] Vec3 prod(Vec3 b) const { return Vec3(x * b.x, y * b.y, z * b.z); }

    [[nodiscard]] double dot_p(Vec3 b) const { return x * b.x + y * b.y + z * b.z; }

    [[nodiscard]] Vec3 f(double b) const { return Vec3(x * b, y * b, z * b); }

    [[nodiscard]] Vec3 norm(double s = 1) const {
        return f(s / sqrt(x * x + y * y + z * z));
    }

    [[nodiscard]] Vec3 p(Vec3 a) const { return Vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x); }
};

struct r {
    Vec3 o, a;

    r(Vec3 j, Vec3 k) : o(j), a(k) {}

    [[nodiscard]] Vec3 p(double t) const { return a.f(t).sum(o); }
};

struct s {
    const Vec3 p;
private:
    const double l;

public:
    s(const Vec3 &p, double l=0) : p(p), l(l) {}
    bool C(r q, double &t) const {
        Vec3 o = q.o.f(-1).sum(p);
        double b = q.a.dot_p(o);
        double c = o.dot_p(o) - l;
        c = b * b - c;
        if (c < 0) {
            return false;
        }
        c = sqrt(c);
        double v = b - c;
        if (v > 0 && v < t) {
            t = v;
            return true;
        }
        return false;
    }
};

int g(double c) {
    return lround(pow(c < 0 ? 0 : c > 1 ? 1 : c, .45) * 255);
}

r C(double x, double y) {
    Vec3 e = Vec3(x, -y, 1).norm(4);
    double a = 6 * drand48(), c = .2 * sqrt(drand48());
    double b = sin(a) * c;
    a = cos(a) * c;
    e.x -= a;
    e.y -= b;
    return {Vec3(a, b), e.norm()};
}


int find_index(r a, double &t, const std::vector<s> &vec) {
    int n = -1;
    for (int m = 0; m < 10; m++) {
        if (vec[m].C(a, t)) {
            n = m;
        }
    }
    return n;
}

Vec3 e(r a, double b, const std::vector<s> &vec) {
    double t = 1e6;
    int o = find_index(a, t, vec);
    if (b > 5 || o < 0) {
        return Vec3();
    }
    if (!o) {
        return Vec3(.9, .5, .1);
    }
    Vec3 P = a.p(t);
    Vec3 V = vec[o].p.f(-1).sum(P).norm();
    if (o > 7) {
        a = r(P, a.a.sum(V.f(-2 * V.dot_p(a.a))));
        return e(a, ++b, vec).f((o - 6.5) / 2);
    }
    double O = 6 * drand48();
    double A = sqrt(drand48());
    Vec3 U = a.a.f(-1).sum(V).norm();
    Vec3 T = U.p(V);
    r a1 = r(P, T.f(cos(O) * A).sum(U.f(sin(O) * A)).sum(V.f(sqrt(1 - A * A))).norm());
    Vec3 j(1, 1, 1);
    if (o == 3) {
        j.x = j.z = 0;
    }
    if (o == 4) {
        j.y = j.z = 0;
    }
    return e(a1, ++b, vec).prod(j);
}

int main() {
    const std::vector<s> u = {{Vec3(0, -2, 5),  1},
                              {Vec3(0, -H),     1e6},
                              {Vec3(0, H),      1e6},
                              {Vec3(H),         1e6},
                              {Vec3(-H),        1e6},
                              {Vec3(0, 0, -H),  1e6},
                              {Vec3(0, 0, H + 3),1e6},
                              {Vec3(-2, -2, 4), 2},
                              {Vec3(2, -3, 4),  1},
                              {Vec3(2, -1, 4),  1}};

    printf("P3\n512 512\n255\n");
    for (int m = 0; m < 512; m++)
        for (int n = 0; n < 512; n++) {
            Vec3 q;
            for (int k = 0; k < 1000; k++) {
                r j = C(n / 256.0 - 1, m / 256.0 - 1);
                q = q.sum(e(j, 0, u).f(0.02));
            }
            printf("%d %d %d ", g(q.x), g(q.y), g(q.z));
        }
    return 0;
}
