/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1215)
#define FUSION_CONVERT_IMPL_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_cons;

                typedef typename build_cons::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
3v7d1nZo8/Zmb+3f3p9veDhYbZ+OOz0hJf9nzzyWvNreO+uOVtqtUy6Re4VyDzGAoOzfCfIc0dcUZzTSX7N6InbEadgJU7ELLsGuWILdcAP2wBuwJ96FvfA+DMAfYW88hH3wSeyLL2A/fB/748c4APmOJQhjcRBOxWBMxiE4H4fiEhyGV6MVN+Nw3IsjcD+OxGMYhm/iKLRQ5nC0YSSuxiiswmjcjKNxK47FWzEGD2IsNuI4ye+XFrkfiGFSn8FyDaxMk5lvNCZKfc7ABZiE6TgT83AWFuJsLMMUvBbn4n6chw9hKh7HK/AvuAA/w4U4gEwswmF4JcbhYkzEJVJfS3EVLsMNuBy34/fwBVyBJzALT2E2foSr8GvMReU+qA2dfWrlvp3czwvQ9/GVvtv9sAZH4BaMwlocj1txMt6I6bgNl+B2LMSb0IE7cAPejFuwDm/DW/B+3Ik/xl34BN6KT+Nt2nt35T4czjd5724N5emP12McbsF4vAHnYK1ufct9NO6vNV/fd1uof9yHo/AenID34lQ8gLPxflyED2AW/hA34kG8B38k5XoYn8NH8EV8FD/EQ/gJ/hS/wp9hd/JzGAfh4xiFT2ACHsEF+BSW4dN4Iz6D2/FZ3IfP4WP4C3wWn8df4AtSj+ctcj8MZ8v2Pli5VpXy/0aOH6/iRHxdynsKF+Absn7fwjx8Bzfg76X8p7EGm7AO/4iP4rv4JJ7BN/A9/Af+GS8lM3/Bfvg+XoYfYCL+FVfhh1LOj3A/nsd25P0T7ISfYl/8DCPxcxyLX+j6bttH6d+7b+y7vY7tYzAWYxiW4Ey0YwGuxyIsx124AR/Aq/AlrMBf49X4G7wG/4xVeA43ovO5HLlXhWNM3vt8pTx3lI4RuFjXx71JvneNfE/fx32lvEc+B8NxFU5FGy7EPFyBqzEL83EdFuAGXOvez0hYtg+T/Sxc0onA/hiJwzEKZ2C0LMdKaJLlDJHlXIKBspxR2nNKco8HB5nUxybmC8RrcSBWy/fCCTHyvX7yvXYYLN+rkO9V6uZPa2H+Mpnfod9eZP53TLaX8czSGyfiMJyESRiPc3EKVmEC1uNUPICJ+GOci4/gFfgCzsff4gI8hWlaPcr1Pw4gMBnqcYRuvkaZL6SV+ZpkvqgW5yNE+zZftsw3vpX56mW+iNbyF+0uR5DHfCu1+eS6DAe0Ml/MaN+Wly3zRbUyX73MN76V+Zpkvggv86Upxy2e9el+M8//EJJv7uTTc2f/Ye984Kua4gD+SlmSJP1ZtbK0VLNq1dKwsvanhsViGNK22mqr/Xm2VVPDIoyKSVEkS6lFmCzN/2EUiqGIwmgYQijy3/fe93v33ft239q/8udzz2e/z3fvvHvO+Z1z7r3v/P0dZZ3ZM/badtdZY0aZaGvKzNaTyTqy2mvI9mar68i09WPbh7c2XUPWH4lFnGvGWs2otW5M1ox5Xi+WRj63w71I2izXGrH827yavE5sHqJfC7YdMdpHN1/35Vtsvt7LuNbr0Gu80l5qJeu8XGu8lpKvZ5AqpFUheURikBxkKVKKVCOtbuc7JBSZgOQghUgZshtptYjvkWjEjixA1iNbkGrEdoe1bsxylrOc5SxnOctZznKWs5zlLHd43OFd/z/TPiFb/V/ZAtCk9f/KOvwdvW3auecFsg7/OQYbe8Mn4Nf+ynyXOmYTeXFMfExYZLyaunPdRfEh1tauaWXc311ic9rntrMMyLE2pcwx1iV+rrOly6Hj/OXsxLQcx7VbHNeKn+sM8ErN/zz1807tc5b6ucqVhhpPjfY5PTE3PTldf3a179GavXP12oPatfgpSUqaudpZ5HHqZ7v2OVYNl6KFS0xjoZQ=
*/