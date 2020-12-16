/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/atomic_ref.hpp
 *
 * This header contains definition of \c atomic_ref template.
 */

#ifndef BOOST_ATOMIC_ATOMIC_REF_HPP_INCLUDED_
#define BOOST_ATOMIC_ATOMIC_REF_HPP_INCLUDED_

#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/atomic_ref_template.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

using atomics::atomic_ref;

} // namespace boost

#endif // BOOST_ATOMIC_ATOMIC_REF_HPP_INCLUDED_

/* atomic_ref.hpp
8tyGPIXkIS8j25CZ6Wy38BWXPIhKeyyYLmSb7P912ILgw6fXN4qwLSwPoup0LevXIea1ztvGta7e4Vq3xuFa1+ByrbvLeq2zff+y4z4tzr4lnfe9yY7Gv3Pz2bhhurn9rzGFzb2m+nZsLpj1vb/krXy04z4kHfV16ahPS0fjEjr7irj5unTcR6Wj38GPFH8wP3CPIPcj+3UcwHCfgUw4FA6Ag+EZso4YQ+ARWBQjv1PyW7wfXozMignGMxwIz4Q5MBuOhoj6nmaujIF+Bs6HY+BXZOxvKTwPXgPPhytl7K8BToDfghfArTAPflfG/J6Bk+FOeJGMzV8s9k6DPTzcxcFBcIaMtRfAy+BM+BX4eXgdnAPvhF+CzbAQ/gIWw7/AEhhDXcvgQGjmuwB+GU6G5bAIVsJVsAreDqvh43AJfAkuhW/AZbAVXgk/gnWwJ/1/NewHr4FZcDkcAb8Ks+EKmA9Xw1J4A6yHN8J74Fp4P/wGfAw2wGb4TfgGvBW+A++Ah+AGeBhuhB/Be2BX+vc+OB5ugVPgw/BS+Ci8DDbBUvhdeCXcBq+F2+Eq+DS8GW6Gt8Efwu/CH8NmuBPuhs/CFvgTWBpjRP7WPbIr+s376DfvT/A7p/0+Ij7YR9Fxvk/ycoqe/5lmdvLP/+b8/+fM+X5crGMN5Wpfy+T9ZVUlan6ZSv8J6c1fs6bXYFZ1FRnU+4O/Wt4flIpf2yTkNPXbR1pvnoF3q2fdKZddVlhZXVxaKCVhy1I9n2UnJTyrpO1neLkHxb/F7R6u4/emzvdS7vdAO9Q94t2Pz1/52ZpX16etedv4zQ0FDW73gm73TG73xJ33LXf/vZT0gfRNXci9VJPcS30X9he/yTPFj3Is3A4nwB3i/9eUFG+0IG7f5+b36z8SG/KTFBeylfaJLtElukSX6BJdokt0iS7RJbr8by+n6Pm/tMxX0ynf/z82PBjfz5D4b7+VeYB7kF1mfL/nHcf/Hcf2k41A/hw9ZnlQrT+pxqAHGeFj0Cla5yw9rvq2Wn9Q6fTyjzkXV1bOLy5ZpP0DROdMtT6L9Z+r9WeC32FlnLqQcAl6rFrrjNDjsfvV+g77HHLSUvmru3pm/oKsU0u1PlCPgxuUbx17fV+V9ZAlzhFdZRnnblXpdwfHMi2xQY6rtEYjEM8oNp2eHOYfA3yLBrkV+fNw/xighzRIXCPz77bjDpjxibA9EJ9Ijet5HcYA56jxFNsYoNpeBOkDtus+UNvLdUwKfzv/v4wP/l69+6mOe+hbW+968ZbX3n9hw6H1s+9xGx90Gwd0e1f0/zc+6Pyuy33c8Ih6ZyXnslyv9kv8kM1IYA5hDhwI1TdtYB48A+bDwXA2HAmL4JmwDGbDpbL9apgD18DRMo53DvwOzIWPwM/AJ+AY+BQcK+N54+CL8Dy4B54PvSc4PhQyNvR/MS703zomdCrHg1KTo+8Yo0t0iS7RJbpEl0/Ccoqe/0tqfLWd8vz/wXBDxxs+3xMSQ1Fi0Bo79fM/D4uOccQlT5L2xd+d2PY4voqv5hLb/H2xZZzEPc5FPGTOsthSWVFVSoUKqxcscPWZH63yDxc7A/rJ2s6itIjPz5e4zRmw2tovVn8b0kgR/sj8/rmTrVVh/v06Puv1Kn+JMYeyxV4pI037znssvvPTdHof7UN9o1ovM+aq6HeXJh1m27YY4iPTz7FDe07pEpOQzDFqrb+KoxxY/3B4+94nHNqp3ydEnFOBzWxTNtti/zVKmyVKwb3kWEt8VreZjlfpcLxJvsQOxyS0xjMeoePnB4/3IzwI5gRtMD/gz+su3repE9CwxUgsq9LvvESnj0qPS1TpNdWLdT/Z0rPUu6naakPPddE=
*/