// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <cmath>
#include <limits>
#include <string>

#include "impeller/geometry/scalar.h"

namespace impeller {

template <class T>
struct TSize {
  using Type = T;

  Type width = {};
  Type height = {};

  constexpr TSize() {}

  constexpr TSize(Type width, Type height) : width(width), height(height) {}

  static constexpr TSize Infinite() {
    return TSize{std::numeric_limits<Type>::max(),
                 std::numeric_limits<Type>::max()};
  }

  constexpr TSize operator*(Type scale) const {
    return {width * scale, height * scale};
  }

  constexpr bool operator==(const TSize& s) const {
    return s.width == width && s.height == height;
  }

  constexpr bool operator!=(const TSize& s) const {
    return s.width != width || s.height != height;
  }

  constexpr TSize operator+(const TSize& s) const {
    return {width + s.width, height + s.height};
  }

  constexpr TSize operator-(const TSize& s) const {
    return {width - s.width, height - s.height};
  }

  constexpr TSize Union(const TSize& o) const {
    return {
        std::max(width, o.width),
        std::max(height, o.height),
    };
  }

  constexpr TSize Intersection(const TSize& o) const {
    return {
        std::min(width, o.width),
        std::min(height, o.height),
    };
  }

  constexpr Type Area() const { return width * height; }

  constexpr bool IsZero() const { return width * height == 0.0; }

  constexpr bool IsPositive() const { return width * height > 0.0; }

  constexpr bool IsEmpty() { return !IsPositive(); }

  constexpr size_t MipCount() const {
    if (!IsPositive()) {
      return 1u;
    }
    return std::max(ceil(log2(width)), ceil(log2(height)));
  }
};

using Size = TSize<Scalar>;
using ISize = TSize<int64_t>;

static_assert(sizeof(Size) == 2 * sizeof(Scalar));

}  // namespace impeller