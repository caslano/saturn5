/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* iter_fold_fwd.hpp
1usr9wfOc7/0krlf+mBL6VPWQfqU3SF9yrJcxmN6CgfiOzgIj+NgNEnfsRsxCgOcxmMaJtfz4Zgi4zEtwFG4FEfjqxiNh3AM/op34O8yPlNN4j4WA3EctsIYbIdx2AHjsSMmYBeciD1xEsqcbfLbCXWx5JvznG2pkh9p2BrN+CBmOvdpzHfc53FPocp36ivHuFqyXjM36xV5uJ6pQOY+crNeWIFn2zMXeJaOwgLPxgcrLnA/Ppi/Ep5zbM/PpdzGOfeplPValrBedAX7u1XeuVqPZ4RyPZfr1c8yh9U5bIe/YGe8gANkztKpMmdpJl6WOUSv4Fb8Q563fciP81gRvdlZJWyMleX66ivXtyo4EKvhEqyOj2It3IK1cS/WwXewLp7B+tiZODfA7tgER2FTTEF/zMRmOB2b4wN4E+7EAPwQWyjxxFuwpzfvM7AvtsLB2BrnYBt8DdviJ9gOf8cgZX0f6n+MwFAcil0wHrvig9gN52MPzMWeuBl74SsYhsexN57EvngBw7F6ReoVbIe3YQT2x2iMwGwcgA/gIFyGkbgdh+AOvB0P4TC8iMPxEo7EGpSDUVgH78TmOBYDcBy2xljsiHHYC+NxAE7AQZiAxWzvcFdvEuvtUV/XU9x0BLBuOMGcz/rPuh8LTmfuKPq//mfPH5XQzfv/oi/snz1/VPim/5w5pErTR3ZL/p/XT/ZAftn6yl7tXFJ/1TxS2d28/2P6zkYWuO8/+2fMI7WMNG8hHCScI9Tp7m0KIyQRVhB2EU4QfHsw7xMhgpBAyCGsJOwjnCXU4YIVSoglzCKsJxwlXCAE9KJeJaQQFhAKCPsIpwh+vAQIIkQSMgnLCNsJRwmm3nyXEEFIISwgFBIOEE71Lh8br/xT/in/eP75q/r/p1hG/7+6sf+UPvf+TmP2+8kz0RasL5qU/kN3Wp6f+vcb0m9Y78iYIb0H94sxp9NfwOS+f9P19FMDXsKxDek7cLv1/wdEDmnfxSTLao2zLwuxLSsea1/WwbbsZceyYNuyxx3L2tuW3eNYFmSSNjJx9mVdLH8Psv8davm7o/3vzjrtGh39srZa2pdMSkw1aNtpmY/e0n7ErG7rJPl7u7R1iiTs5//Exlj2G5ORmU5j7A6WNBj3kfJ37iMl7Uz5piwD0zSCql23HN9wH+mr5c1zoliB41tk3X8cbY+cj7Hb9rK2Y+s3wXFsL8fZ872z7VhscyzraFvWJs7pmMnx2RmrPj4vxKqPz6/x/O3ULzBWjoW6ra5+uyeztt2TtCmSY2mZzUL6sUi+Snso6cfi1IYodYK083IuC442nmZZTzmgnHCWtkbLlMcU8j+Ff5N02tsrVbK0leJ0luPlXGYipQ+88htrY7wefZT+SwmWbUxIM0+PSZwal5zi4Rh6vhMdeajJF4mT4mhbujJk/DxJP/madjcNQZ3baq2wxD91qqP9W4nniP3cetvyPek/pOoXZUmRKh8CK8nvJUS+Ps7ESkpf1omOfEjOyJiWmO6+nbeSD0FJmrKkyYckl3yQtMmyZOpgR7zb1lK3iY5wkwfOafOVMQd+kfaPZwm+pC3PGseEtJiE5HRmu/CkDbuStpRkbdoccZG0qcu4UVmQsS7V7RuDVH21JF/U5UCVvtOSvsEyJmQEKukrTralLy0zKdGSQrfpu5r02I6BWermeqp+Z5x/SpXp6A/MerI8kxFmpC9YjcnWc7d2bXXduqKKXP85x9uJVUljzhTb2KTaunWul246+7JBruFda9IOg/172evZ2DRHPeuVZqsbOwTZ6tTbptqWBduvjZdStNfafSnaOnpZiraOjk3RXn87pmjr7aop6nr7iymO66iSl7le+uN0rvA=
*/