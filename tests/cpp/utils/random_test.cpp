//=============================================================================
//    Copyright (C) 2021-2024 Wageningen University - All Rights Reserved
//                     Author: Gonzalo Mier
//                        BSD-3 License
//=============================================================================

#include <gtest/gtest.h>
#include "fields2cover/utils/random.h"
#include "fields2cover/types.h"

TEST(fields2cover_utils_Random, init) {
  f2c::Random rand1(1);
  double d1 = rand1.getRandomDouble();
  double d2 = rand1.getRandomDouble();
  EXPECT_NE(d1, d2);

  f2c::Random rand2(rand1);
  d1 = rand1.getRandomDouble();
  d2 = rand2.getRandomDouble();
  EXPECT_EQ(d1, d2);

  f2c::Random rand3 {rand1};
  d1 = rand1.getRandomDouble();
  d2 = rand3.getRandomDouble();
  EXPECT_EQ(d1, d2);

  rand2 = rand1;
  d1 = rand1.getRandomDouble();
  d2 = rand2.getRandomDouble();
  EXPECT_EQ(d1, d2);

  std::vector<f2c::Random> v_rand {rand1, rand2, rand3};


  for (auto&& r : v_rand) {
    auto r2 = r;
    d1 = r.getRandomDouble();
    d2 = r2.getRandomDouble();
    EXPECT_EQ(d1, d2);

    f2c::Random r3 = r;
    d1 = r.getRandomDouble();
    d2 = r3.getRandomDouble();
    EXPECT_EQ(d1, d2);
  }
}


TEST(fields2cover_utils_Random, get_angle_random) {
  f2c::Random rand;
  auto rand_val {0.0};
  auto two_pi = boost::math::constants::two_pi<double>();
  for (int i = 0; i < 10000; ++i) {
    rand_val = rand.getAngleRandom();
    EXPECT_LT( rand_val, two_pi);
    EXPECT_GE( rand_val, 0.0);
  }
}

TEST(fields2cover_utils_Random, get_random_double) {
  f2c::Random rand;
  const int N = 10000;
  double sum_val {0.0};
  for (int i = 0; i < N; ++i) {
    auto rand_val = rand.getRandomDouble();
    EXPECT_LT( rand_val, 1.0);
    EXPECT_GT( rand_val, 0.0);
    sum_val += rand_val;
  }
  EXPECT_NEAR(sum_val, N/2, N/10);

}

TEST(fields2cover_utils_Random, get_linear_random) {
  f2c::Random rand;
  auto rand_val {0.0};
  for (int i = 0; i < 10000; ++i) {
    double max_rand = rand.getRandomDouble();
    double min_rand = rand.getRandomDouble() - 1.0;
    rand_val = rand.getRandomLinear(min_rand, max_rand);
    EXPECT_LT( rand_val, max_rand);
    EXPECT_GE( rand_val, min_rand);
  }
}

TEST(fields2cover_utils_Random, get_exp_random) {
  f2c::Random rand (42);
  auto rand_val {0.0};
  for (int i = 0; i < 100; ++i) {
    double max_rand = rand.getRandomDouble() + 1.5;
    double min_rand = rand.getRandomDouble() + 0.5;
    rand_val = rand.getRandomExp(min_rand, max_rand);
    EXPECT_LT( rand_val, max_rand);
    EXPECT_GE( rand_val, min_rand);
  }
}

TEST(fields2cover_utils_Random, get_random_exp_dist) {
  f2c::Random rand (42);
  size_t count0To1 = 0;
  size_t count1To2 = 0;
  size_t count2To3 = 0;
  size_t count3To4 = 0;
  size_t count4ToInf = 0;
  size_t n = 1e4;
  for (size_t i = 0; i < n; ++i) {
    auto d = rand.getRandomExpDist(1.0);
    EXPECT_GE(d, 0.0);
    if (d <= 1) {
      ++count0To1;
    } else if (d <= 2.0) {
      ++count1To2;
    } else if (d <= 3.0) {
      ++count2To3;
    } else if (d <= 4.0) {
      ++count3To4;
    } else {
      ++count4ToInf;
    }
  }
  EXPECT_EQ(n, count0To1 + count1To2 + count2To3 + count3To4 + count4ToInf);
  EXPECT_GT(count0To1, count1To2);
  EXPECT_GT(count1To2, count2To3);
  EXPECT_GT(count2To3, count3To4);
  EXPECT_GT(count3To4, count4ToInf);
}


TEST(fields2cover_utils_Random, mod_2pi) {
  const double two_pi {boost::math::constants::two_pi<double>()};
  for (double i = 0.01; i < 100.0; i += 0.1) {
    auto ang = i;
    EXPECT_NEAR(fmod(ang, two_pi), F2CPoint::mod_2pi(ang), 1e-3);
    EXPECT_EQ(i, ang);
    EXPECT_NEAR(fmod(1e5 * two_pi - i, two_pi),
        F2CPoint::mod_2pi(-i), 1e-3);
  }
}

TEST(fields2cover_utils_Random, genRandField) {
  f2c::Random rand;
  auto field = rand.generateRandField(1e2, 4);
  EXPECT_NEAR(field.area(), 1e2 , 1e-6);
  EXPECT_THROW(rand.generateRandField(1e2, -2), std::invalid_argument);
  EXPECT_THROW(rand.generateRandField(1e2, 0), std::invalid_argument);
  EXPECT_THROW(rand.generateRandField(1e2, 2), std::invalid_argument);
  EXPECT_THROW(rand.generateRandField(-1e2, 6), std::invalid_argument);
}

TEST(fields2cover_utils_Random, isConvex) {
  f2c::Random rand(4);
  int n {100};
  auto field = rand.generateRandField(1e2, 3);
  auto poly = field.getField().getCell(0);
  int convex_fields {0}, non_convex_fields {0};
  for (int i = 0; i < n; ++i) {
    field = rand.genConvexField(1e2);
    if (field.getField().isConvex()) {
      ++convex_fields;
    }
  }
  EXPECT_GT(static_cast<double>(convex_fields) / n, 0.9999);

  for (int i = 0; i < n; ++i) {
    field = rand.genNonConvexField(1e2);
    if (!field.getField().isConvex()) {
      ++non_convex_fields;
    }
  }
  EXPECT_GT(static_cast<double>(non_convex_fields) / n, 0.9999);

  EXPECT_FALSE(F2CCell().isConvex());
}



