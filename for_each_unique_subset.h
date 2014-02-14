// for_each_unique_subset(): Given a tuple, invokes a function
// for each subset of non-null fields that could be nullified.
// Handles arithmetic types, empty std::string-s and "0"-s in enum classes.
//
// Used by Marvin for log entries grouping.
//
// Example:
//
// enum class is_mobile { all = 0,  mobile, desktop };
// typedef std::tuple<int, is_mobile, std::string> TEST_TUPLE_TYPE;
// TEST_TUPLE_TYPE key(0, is_mobile::mobile, "test");
// for_each_unique_subset(key, [](const TEST_TUPLE_TYPE& value) {
//   std::cout << std::get<0>(value) << ' ' << static_cast<size_t>(std::get<1>(value)) << ' ' << std::get<2>(value) << std::endl;
// });
//
// Prints 4 (== 2^2) lines, since two fields -- indexes 1 and 2 -- are nonzero.

#ifndef FELICITY_FOR_EACH_UNIQUE_SUBSET_H
#define FELICITY_FOR_EACH_UNIQUE_SUBSET_H

#include <iostream>
#include <tuple>
#include <string>

namespace felicity {

template<typename T> struct is_default_value_impl : std::enable_if<std::is_arithmetic<T>::value> {
  static bool impl(const T& x) {
    return !static_cast<size_t>(x);
  }
};

template<> struct is_default_value_impl<std::string> {
  static bool impl(const std::string& s) {
    return s.empty();
  }
};

template<typename T> bool is_default_value(const T& x) {
  return is_default_value_impl<T>::impl(x);
}

template<typename T, typename F, size_t I, size_t N> struct for_each_unique_subset_impl {
  static void call(T& key, F f) {
    for_each_unique_subset_impl<T, F, I+1, N>::call(key, f);
    if (!is_default_value(std::get<I>(key))) {
      typedef typename std::tuple_element<I, T>::type TYPE;
      TYPE e = TYPE();
      std::swap(std::get<I>(key), e);
      for_each_unique_subset_impl<T, F, I+1, N>::call(key, f);
      std::swap(std::get<I>(key), e);
    }
  }
};

template<typename T, typename F, size_t N> struct for_each_unique_subset_impl<T, F, N, N> {
  static void call(T& key, F f) {
    f(key);
  }
};

template<typename T, typename F> void for_each_unique_subset(T& key, F f) {
  for_each_unique_subset_impl<T, F, 0, std::tuple_size<T>::value>::call(key, f);
}

}  // namespace felicity

#endif
