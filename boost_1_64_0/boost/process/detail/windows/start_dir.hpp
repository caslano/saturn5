// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_START_DIR_HPP

#include <string>
#include <boost/process/detail/windows/handler.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
struct start_dir_init : handler_base_ext
{
    start_dir_init(const std::basic_string<Char> &s) : s_(s) {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        exec.work_dir = s_.c_str();
    }

    const std::basic_string<Char> &str() const {return s_;}
private:
    std::basic_string<Char> s_;
};

}}}}

#endif

/* start_dir.hpp
rGebnszYuu1M9y0bHhjEvhkJz+QKi36d0+fJIQvqDXw6pFmpMzbbG3aHeWRw6r2f9jk/vl7NVYtmzXjxV/onkm7XT+wNWPPQnGXdvrySnDG0ZiF7q30c5pc69Y6ZUmdp/lvR7ZaWKrzxT85jF/2uvVIqfDfocoNSWTGFs5tfextzSZ+7Y9OuPDhsTH3fqWOCZp1L+4y+kKR/u6t1ave/Muvhl7oNiT5fcsls+j8S/tcenbS8Qf6u0aei/nzp1zpVHYMzSZ93jwz66YXMimdvPl7Q+avqO4soQ+L/9u8GV10z8sXABUEH7ZFXNr/O+yUSzi2DHxh0vsTSjQ89X67w4KbH9vE+ufhzY9Sm9H0xtdscGvBWwBuHXq1PuWzpMC9TfVPDNUE/2Bc1j/VJb/Z3wj9JzEOabm7fYkKJlOPvvn5u05bXXiI8Ev4jMz/74Oavj16esaRK1M78oeTBH5o5zHcd3nnsj4rdZr4Xn/3p+83eXcp85gyH+SMH282uczFz6ycbe/SOnnPgM9J/lMM86bGpG1IPTXirWaVPFu46+hn3DJPn/uyOJ9858uGkazPDdoXXD7jK+Z6UG8wfCFu1d++kCvcfembs3wvrDm1BeZT47ry7x+XrbVp89sS5U/tT7CmfEH7JJ2Onp2yrkv6d35SW3f728ICvxtNuSjrM37z28+/3x8XN2d9vesYjm8g//xD9rRd2DE/Yu3mp/ZcbPcs9XrAZc4lvhXdm5V+vPujNh6fft2PhG9sOsj/G0QeRCsX5zfF0u7Of9a7h98FI9+/GofKbllDObNa/hxp+NzHobC3n/H3akQUMv49Gun/7GMzbhLp/X41w/r5ukzOa9e+f3b9l/ibex3neZIDhd/0I9++u6Nfh90Z+dzP8vqh+kwy2S4bfnxl+33T9RmxR+recwdmKMMzzkXda5PfjvjLvI7/v85NvAsnvUuTxQvU7lt8r1e+a/nKWhPweyPMpp/wczu/vlM5D/P5Q/c7n9wfq90p+v61+f8/vvSoMPpS/fcq8JL+LHHFDQginHXa1O+0qOtoTVcmfK2nLDYS/wGbwMrwX/gr7wN9gBvwD5sDrcAG8AddCGrvcZ4AdboN+8E1YAr4HS8LDMACegYHwBxgML8Ey8FdYFv4By8EShDEUBsNyMAqWhtXVdT0YAZvBSNgBRsHOMBo64v08QjmReO9EHPEOg+tUvE/RaPrAH2EMPAurwXOwFrwGa8OfYEt4HnaHF2BvZd8HXoQj4SWYAf8FH1Tmj8CrcLnSXwGL4FZ4Gb6szItgHUT2zcMSiDxPGKPC+z7xcvAALFL2cUq/oY/zuoZz7kf+BuBvVTgUtoLDYCJcB9PgcDgVjoDzYBJ8GI5U4U6Gj8MUuFm52w3T4GdwNDwDx8DfYTq8ATOgH2EYC0vB+bA9XAB7w4WwH3wYjoZ5cBx8FObCZXAxfAyuho/DZ+EKuAk+AV+HK+EbcDX8CK6Bn8In4RG4Fv4E10FHQi6B4XCdSu9cZCQJbYe7VXqWhpMRmWcJIP3g57AJ/AK2hcfh3fAc7A+/hmPhSZgFv4Wz4Sn4KPweroA/wrXwLFyv3BfBQUhsScIBz6lwBMAeKhw7Ca+sqcGP4evwMHwLHoFvwC/hbngGvgnPKvsiuAwJwUM7fFz5XxbOV/6vRy8IboAxcCNsBDfBJnAzbA53wJbwBdgWvgiHwW0wDW6H6UpvLNwK5yv7R5T9MmVfBEc6zFS40HPWlbC/CtceFe99MBW+p/x/H2bCj+B4eABOhh/A2fBDOE/s3c85vpQ6X8biOX+CnjxvGASPwIrwM1gFHoNx8AsYD4/D7vBL2B9+BQfCk3AQPAGT4TdwjDIvgok=
*/