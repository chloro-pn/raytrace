#ifndef VALUE_COMPARE_H
#define VALUE_COMPARE_H

template<typename T>
bool value_equal(const T& t1, const T& t2) {
  return (t1 - t2) >= -10e-4 && (t1 - t2) <= 10e-4;
}

template<typename T>
bool value_be(const T& t1, const T& t2) {
  return (t1 - t2) >= -10e-4;
}

template<typename T>
bool value_se(const T& t1, const T& t2) {
  return (t1 - t2) <= 10e-4;
}

template<typename T>
bool value_b(const T& t1, const T& t2) {
  return (t1 - t2) > 10e-4;
}

#endif // VALUE_COMPARE_H
