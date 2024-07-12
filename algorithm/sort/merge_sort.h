#ifndef Y0_CCUTIL_ALGORITHM_SORT_MERGE_SORT_H
#define Y0_CCUTIL_ALGORITHM_SORT_MERGE_SORT_H

#include <iostream>
#include <vector>

template<typename T>
std::enable_if<std::is_arithmetic<T>::value, void>::type
merge(std::vector<T> &v,
      const size_t &kleft,
      const size_t &kmiddle,
      const size_t &kright) {
  const size_t kleft_vec_size = kmiddle - kleft + 1;
  const size_t kright_vec_size = kright - kmiddle;
  std::vector<T> left_vec(kleft_vec_size);
  std::vector<T> right_vec(kright_vec_size);

  for (size_t i = 0; i < kleft_vec_size; ++i)
    left_vec.at(i) = v.at(kleft + i);
  for (size_t i = 0; i < kright_vec_size; ++i)
    right_vec.at(i) = v.at(kmiddle + i + 1);

  size_t i = 0;
  size_t j = 0;
  size_t k = kleft;

  while (i < kleft_vec_size && j < kright_vec_size)
    v.at(k++) = left_vec.at(i) < right_vec.at(j) ?
                  left_vec.at(i++) : right_vec.at(j++);
  while (i < kleft_vec_size)
    v.at(k++) = left_vec.at(i++);
  while (j < kright_vec_size)
    v.at(k++) = right_vec.at(j++);
}

template<typename T>
std::enable_if<std::is_arithmetic<T>::value, void>::type
merge_sort(std::vector<T> &v,
           const size_t &kleft,
           const size_t &kright) {
  if (kleft >= kright)
    return;
  const size_t kmiddle = kleft + (kright - kleft) / 2;
  merge_sort(v, kleft, kmiddle);
  merge_sort(v, kmiddle + 1, kright);
  merge(v, kleft, kmiddle, kright);
}

#endif
