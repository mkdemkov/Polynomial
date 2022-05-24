#include <vector>

template<typename T>
class Polynomial {
 public:
    std::vector<T> polynomial;
    using const_iterator = typename std::vector<T>::const_iterator;

    void DeleteEmpty(std::vector<T> &vec) const {
        std::vector<int> indexes;
        for (int i = vec.size() - 1; i > 0; --i) {
            if (vec[i] == T()) {
                indexes.push_back(i);
            } else {
                break;
            }
        }
        for (auto i : indexes) {
            vec.erase(vec.begin() + i);
        }
    }

    explicit Polynomial(std::vector<T> &vec) {
        polynomial = vec;
        DeleteEmpty(polynomial);
    }

    explicit Polynomial(T coef = T()) {
        polynomial.push_back(coef);
    }

    template<class Iter>
    Polynomial(const Iter beg, const Iter end) {
        Iter it = beg;
        while (it != end) {
            polynomial.push_back(*it);
            it++;
        }
        DeleteEmpty(polynomial);
    }

    bool operator==(const Polynomial &other) const {
        return (polynomial == other.polynomial);
    }

    bool operator==(const T &other) const {
        Polynomial another(other);
        return (another == *this);
    }

    bool operator!=(const Polynomial &other) const {
        return (polynomial != other.polynomial);
    }

    bool operator!=(const T &other) const {
        Polynomial another(other);
        return (another != *this);
    }

    Polynomial operator+(Polynomial other) const {
        auto maximum = std::max(polynomial.size(), other.polynomial.size());
        auto ann = polynomial;
        if (ann.size() != maximum) {
            for (size_t it = 0; it < maximum; ++it) {
                ann.push_back(T());
            }
        }

        if (other.polynomial.size() != maximum) {
            for (size_t it = 0; it < maximum; ++it) {
                other.polynomial.push_back(T());
            }
        }
        std::vector<T> res(maximum);
        for (size_t it = 0; it < maximum; ++it) {
            res[it] = ann[it] + other.polynomial[it];
        }
        DeleteEmpty(res);
        return Polynomial(res);
    }

    Polynomial operator+(T other) {
        Polynomial another(other);
        return (another + *this);
    }

    Polynomial operator-(Polynomial other) const {
        auto maximum = std::max(polynomial.size(), other.polynomial.size());
        auto ann = polynomial;
        if (ann.size() != maximum) {
            for (size_t it = 0; it < maximum; ++it) {
                ann.push_back(T());
            }
        }

        if (other.polynomial.size() != maximum) {
            for (size_t it = 0; it < maximum; ++it) {
                other.polynomial.push_back(T());
            }
        }
        std::vector<T> res(maximum);
        for (size_t it = 0; it < maximum; ++it) {
            res[it] = ann[it] - other.polynomial[it];
        }
        DeleteEmpty(res);
        return Polynomial(res);
    }

    Polynomial operator-(T other) {
        Polynomial another(other);
        return (*this - another);
    }

    friend Polynomial operator-(T first, Polynomial other) {
        Polynomial another(first);
        return (another - other);
    }

    Polynomial &operator+=(Polynomial other) {
        *this = (*this + other);
        return *this;
    }

    Polynomial &operator+=(T other) {
        Polynomial another(other);
        return *this += another;
    }

    Polynomial &operator-=(Polynomial other) {
        *this = (*this - other);
        return *this;
    }

    Polynomial &operator-=(T other) {
        Polynomial another(other);
        return *this -= another;
    }

    T operator[](size_t index) const {
        if ((index >= 0) && (index < polynomial.size())) {
            return polynomial[index];
        }
        return T();
    }

    [[nodiscard]] long long Degree() const {
        if (polynomial.size() == 1) {
            if (polynomial[0] == T()) {
                return -1;
            }
            return 0;
        }
        return polynomial.size() - 1;
    }

    [[nodiscard]] const_iterator begin() const {
        return polynomial.cbegin();
    }

    [[nodiscard]] const_iterator end() const {
        return polynomial.cend();
    }

    Polynomial operator*(Polynomial other) const {
        std::vector<T> res(polynomial.size() * other.polynomial.size());
        for (size_t i = 0; i < polynomial.size(); ++i) {
            for (size_t j = 0; j < other.polynomial.size(); ++j) {
                res[i + j] += (polynomial[i] * other.polynomial[j]);
            }
        }

        return Polynomial(res);
    }

    Polynomial operator*(T other) {
        Polynomial another(other);
        return (another * (*this));
    }

    Polynomial &operator*=(Polynomial other) {
        *this = (*this) * other;
        return *this;
    }

    Polynomial &operator*=(T other) {
        Polynomial another(other);
        *this *= another;
        return *this;
    }

    [[nodiscard]] T VStepen(T uk, size_t it) const {
        T res = T(1);
        for (size_t i = 0; i < it; ++i) {
            res *= (uk);
        }
        return res;
    }

    T operator()(const T &uk) const {
        T res = T();
        for (size_t it = 0; it < polynomial.size(); ++it) {
            res += (polynomial[it] * VStepen(uk, it));
        }
        return res;
    }
};
