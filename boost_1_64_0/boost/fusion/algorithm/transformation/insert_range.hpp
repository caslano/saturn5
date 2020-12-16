/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_009172005_1147)
#define FUSION_INSERT_RANGE_009172005_1147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Position, typename Range>
        struct insert_range
        {
            typedef typename convert_iterator<Position>::type pos_type;
            typedef typename result_of::begin<Sequence>::type first_type;
            typedef typename result_of::end<Sequence>::type last_type;

            typedef iterator_range<first_type, pos_type> left_type;
            typedef iterator_range<pos_type, last_type> right_type;
            typedef joint_view<left_type, Range> left_insert_type;
            typedef joint_view<left_insert_type, right_type> type;
        };
    }

    template <typename Sequence, typename Position, typename Range>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::insert_range<Sequence const, Position, Range const>::type
    insert_range(Sequence const& seq, Position const& pos, Range const& range)
    {
        typedef result_of::insert_range<Sequence const, Position, Range const> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::left_insert_type left_insert_type;
        typedef typename result_of::type result;

        left_type left(fusion::begin(seq), convert_iterator<Position>::call(pos));
        right_type right(convert_iterator<Position>::call(pos), fusion::end(seq));
        left_insert_type left_insert(left, range);
        return result(left_insert, right);
    }
}}

#endif


/* insert_range.hpp
8Tj646cYiydwIf4dN+BJzMTPlfzwS9yD/8BT+BX+gOfxPur7W2yA36EHfo/N8QJ2x4s4AC/hQLyCQ7AI5+NPmIrXcBH+ijvwBr6ON3E3/obyfmkZL5/t2OT90n73qe93GonNMAC74CgciGNwFAZiCI7FGTgO52EQLsUJuBYnYjZOwjwMxn/gZLyJU1DeFyjj55u/5/lFV7Vc27Eh7sDG+BK2wpexH+5E7f1azM/Re39nkW8ljMMaGI/F6TIlXW27dOiqpmuJtbCVLr+8EtJ1l3Q9JF1PXbrCEtJ5Sboukq6rlo6fVY6X7xtZvnOyfOdR0jF+u+P8+kh+fSU/H11+viWkOyb5HUclXb4uv9ASypkg6RKlnEmSzpdIk3R9Td4T21baQztshu2xJXbAHthRV+6CEvJ/XfJ/Q/LfrSt3UQnpdkm6VyTdq7p07qsdp3te0m2SdJu1dEQJ6d6SdG9LuhxdusAS0m2RdFsl3TZdOstqx+vzkKQ7LOvziC5degnpGkr7aSTtp7FuPWRLulom6SpLuirojq769VdCOndJV0vS1UZt/Um6ribpnJmuHlbAjuiipSMyHOf3sdRLAbrjJ/r1kOF4PeyQdFmyHl7Sr4cS0q2VdOsk3Xr9eigh3V5Jlyvp9unSZWc4Xn95km6/rPcDunQFJdTLCUn3d6mXk/rtqIRyrpZ0GVLOZ/Xb0bOO0y2VdMsk3dOSLqsCaSUdY/iSTr3XbiMqP69Jf5GNbfEN6S9242Dcg+PwTZyKb2Ecvo0LMAefxndwPb6LL+FezMFcPIL78HP8G36P7+ENzMPKFG4/1sUD2BLfx+54EP3xEAbhEYzHYzgPj+MK/BA34cf4BhbgYfwUT+IJvIR/x9v4OSrHS19gczyNPfAMDsGzOAW/wjj8Gh/Dc7gKz+N2/A7fwgt4DC/iWfwBf8Ar+Af+iPe7sO6xBf6MPfEajsRf8CG8gfF4ExfhP3E13sId+DvuxT/wODqznr/CCvgrVkTlOKoy1scq2AJdcSjehwFYE4PQHWdjbVyOdXA11sU92AD34gNKPtgQz2MzvIbN0ZV21QLrYUtsgq3QG9viBGyPIdgB07AbPo3eSr7YHbX3jss4wBEm7x1fz3JXxw3SXp/HLrgJJ+BmnIwv4CO4Rfqxm0S2zPcZeY9nY3luRvmJZjoPnImtMRY7Yxz2QQsOxdk4GhMwAZMwBefiEpyHqzAZN+NjuB0fx2P4BH6Ci/ArfAq/wyVSzmX4Gz4t28UzWB2XYxdcIdvFKhyJq/EhzMDZ+Cw+gc/hU7hG68dlbGR8wKT/GMx0VdEfG+AQ/XGcpGtsku7KfWq6H7ERXsXi92UXSbpeJu/L/l5pn3gBW+JF7IaXtOMdGSMYe5sc7/hIvv2wAfbHNjgAe6Gvfr+w2fFyz5P5JMt8UnTlz5Z0/iblT5XyP4qd8TH0xcf1/XWm43wHSH37Sn0P1O9vMx3Xd1NJ54GNsBlq74WXdCNMzhe+kPJ+ia3wDHbCf2BXPIv++BVq613m19GkHA8r2zs+IvU+9U46Nj7Hy12N8t6HbrLc1XXL7VFCurqSrp6kq68/Dpd0PibpblVR6+l37Im3UWsXLzhevnBZvghZvkj9fl/SdTZJN1yOo8ZgOwzUyiljgGI3k3TRsv3EyHqZoT+O2uI4v/GSX7DkNxm15dviuD5XSLv/q7T7dP3xUAnpFkm6xZLuSX29SLoWJuk+r6yen5zCJvgFWs+/K8iYkpAuxydjlPmjvPPK2s+fwx54HgfjtzgBL2ME/ogz8SomYhEuwZ9wBf6MW/Eavo7X8T38BY/hr5iPN/EE/oZn8J9YhP/CG3gL3Sjs79gQb2Mb/AO7YQU=
*/