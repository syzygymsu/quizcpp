#include <cmath>
#include <cstdio>

double drand48();

double H = 1003;

struct Vec3 {
    double x, y, z;

    explicit Vec3(double a = 0, double b = 0, double c = 0) {
        x = a;
        y = b;
        z = c;
    }

    Vec3 a(Vec3 b) { return Vec3(x + b.x, y + b.y, z + b.z); }

    Vec3 c(Vec3 b) { return Vec3(x * b.x, y * b.y, z * b.z); }

    double e(Vec3 b) { return x * b.x + y * b.y + z * b.z; }

    Vec3 f(double b) { return Vec3(x * b, y * b, z * b); }

    Vec3 n(double s = 1) {
        return f(s / sqrt(x * x + y * y + z * z));
    }

    Vec3 p(Vec3 a) { return Vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x); }
};

struct r {
    Vec3 o, a;

    r(Vec3 j, Vec3 k) {
        o = j;
        a = k;
    }

    Vec3 p(double t) { return a.f(t).a(o); }
};

struct s {
    Vec3 p;
    double l = 0;

    int C(r q, double &t) const {
        Vec3 o = q.o.f(-1).a(p);
        double b = q.a.e(o);
        double c = o.e(o) - l;
        c = b * b - c;
        if (c < 0)return 0;
        c = sqrt(c);
        double v = b - c;
        if (v > 0 && v < t) {
            t = v;
            return 1;
        }
        return 0;
    }
};

int g(double c) {
    return pow(c < 0 ? 0 : c > 1 ? 1 : c, .45) * 255 + .5;
}

r C(double x, double y) {
    Vec3 e = Vec3(x, -y, 1).n(4);
    double a = 6 * drand48(), c = .2 * sqrt(drand48());
    double b = sin(a) * c;
    a = cos(a) * c;
    e.x -= a;
    e.y -= b;
    return {Vec3(a, b), e.n()};
}

s u[10] = {{Vec3(0, -2, 5),  1},
           {Vec3(0, -H),     1e6},
           {Vec3(0, H),      1e6},
           {Vec3(H),         1e6},
           {Vec3(-H),        1e6},
           {Vec3(0, 0, -H),  1e6},
           {Vec3(0, 0, H + 3),
                             1e6},
           {Vec3(-2, -2, 4), 2},
           {Vec3(2, -3, 4),  1},
           {Vec3(2, -1, 4),  1}};

int p(r a, double &t) {
    int n = -1;
    for (int m = 0; m < 10;
         m++) {
        if (u[m].C(a, t))n = m;
    }
    return n;
}

Vec3 e(r a, double b) {
    double t = 1e6;
    int o = p(a, t);
    if (b > 5 || o < 0)return Vec3();
    if (!o) {
        return Vec3(.9, .5, .1);
    }
    Vec3 P = a.p(t);
    Vec3 V = u[o].p.f(-1).a(P).n();
    if (o > 7) {
        a = r(P, a.a.a(V.f(-2 * V.e(a.
                a))));
        return e(a, ++b).f((o - 6.5) / 2);
    }
    double O = 6 * drand48();
    double A = sqrt(drand48());
    Vec3 U = a.a.f(-1).p(V).n();
    Vec3 T = U.p
            (V);
    a = r(P, T.f(cos(O) * A).a(U.f(sin(O) * A)).a(V.f(sqrt(1 - A * A))).n());
    Vec3 j(1, 1, 1);
    if (o == 3)
        j.x = j.z = 0;
    if (o == 4)j.y = j.z = 0;
    return e(a, ++b).c(Vec3(j));
}

int main() {
    printf("P3\n512 512\n255\n");
    for (int m = 0; m < 512; m++)
        for (int n = 0; n < 512; n++) {
            Vec3 q;
            for (int k = 0; k < 1000; k++) {
                r j = C(n / 256.0 - 1, m / 256.0 - 1);
                q = q.a(e(j, 0).f(0.02));
            }
            printf("%d %d %d ", g(q.x), g(q.y), g(q.z));
        }
    return 0;
}
