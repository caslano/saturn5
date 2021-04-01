/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))

#endif

/* assume_aligned_gcc.hpp
6YaIzROIVm9EEgXgQ7Ta8ga6O1wxr0DkFcAiynbqZXm96hg5FTvFVG8FVLStnW+0NCFdKBPZV0QwmZhw+CCWGFnXZNS0Q+8UIxBARuUZnxWoX8teJOZdBzQyzI8gsY4UUQgzJ0nSq0/md2jlyIj+cMk4zZNb2ue588g3I4BMhnyMJBoUoAhsmRt2cEQuBmdH8YX/SNrwad5nKsxNqryDlwKiya0nr8Z0WtrPe5X0SAooHod4p88E+noUm6a7DIf8qCTfeP0xffoYadg1aJj0vwI6m82IQFOOgD1HplJb6dE9bieYRWCod4JcnZt/uuSdcYPFdn9r+VEgjjdHwdVYGFzIwQaouE8zk17F3x/qzdQfZs7XtpX8XhBrfY2j9nq6i5/W/saAvdvTJuEN/4vemQtTcMxwZc23D1Hcv2BKPVo+AsEkb3ABZZE4H/OIe9RmiWgJRkNa2BKs3hEggVMRKIdROf1CeDZEWM+PunJJaZWahnjPwSStRxJyefYVuMzpjHXkVw53hPoNizJBDDx66R3ouNNCPw41AsqpSgS6AwPSuftynMwSx/HNOg==
*/