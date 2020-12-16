/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_07162005_0235)
#define FUSION_PUSH_BACK_07162005_0235

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_back
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<Sequence, single_view const> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_back<Sequence const, T>
        >::type
    push_back(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_back<Sequence const, T> push_back;
        typedef typename push_back::single_view single_view; 
        typedef typename push_back::type result; 
        single_view x_(x);
        return result(seq, x_);
    }
}}

#endif


/* push_back.hpp
uuMElP5axj2krZr0192V+yawB3bE3tgP+2Aw9sUY7IezsL/0W8FEpsw3UubrigEy3zDpt8LRByNwKEZiEEbhQzgNH8bpOBWjpX+izcv4gRwTSLtso8xf2mVd+V6qHnpgfWyLDbE3NkI/bIyj8EGcjE0wFD1wBjbDudgcH8UWuBY9cRu2wp3YFq3HHfgBtsfPsAN+hR2lf+uM19ELK1BWb6yK3bET9kDr9RIcib1wFPbGSOyDcdgXLeiD83AgbsZB+Bb64VkcjL+gPyrfEw/BmjgUa+EwrIcjsAEGSD/J+/Jk3EL6HKnfVk7kJ/W7RK4fLcW2uAz9cCWOxVX4EK7GSMzAGFyDi3EtpuN6fBE34Gu4EffgJtyLm/EUvoDf4Bb8CbdiNaV/x3q4G/viHhyHb2I6vo1rMAd34Tt4DPfiJ7gfL+IBLMKj6MyyfoC18Rg2w+PYE/OxL36EAfgxTsQCtOCnOAc/w/l4AqUfkHEPlfEQ7fsB2hbtlbpGD1yIA3ARDsXFOBqfwgRcgk/iUlyLy3A9Po0b8RnchcsxB1fgfvwrforp+DmuRLluI2MZ0seaXLeZ6ayWLxY9MB4D0IIROBsfwwR8ChMxHZNwJ87BXJyLeZiMx3A+fowL5HpYKsr1fxmjUCmH/fX/6ZT7PozG6hgjy+FB+Eq6ZvK9ijNRR9Ll66azyHRtS5kuu4T5vaibrlCbX0nTEW7a/PiewXa6NbrpAt1kfqVMl66bn5ch32900+XJdO1LnI6f6pJvKdP5Vnec71l9PWvzK3m67OqOyxemm65Iy7ek6YgaZZsuUKarX8p0ljLOL7OM0xXUKNvyutcs23SBMl23UqZLl+nallY+ma4Z4VvBdrpu+vbiLvNzOJ18nyfTNSeCDdtzPfneqD4+iA2w+PjEIunWmRyfPM/8m+Em9MLNGI+ZOBdfkH5yC2bgVpTnoWRsIHkey/A81CtMVw9fxZb4GnpjtqTPIdIkfb4c1ynLvEvSF8h9dGdwIf4Dn5X2vge/wn34NV7Bc3gdz2Nj5XgVW+JFnIKXMAx/wOl4FVOxSJk//oRr8Gd8Hn/FN/AGvo838Qj+JuU/6iRj+OBjUn5leXOL+9fKlANnYmeMlf37LAzGONmvW3AWJuBSTMTnMEnuY5yDB3AefoDJ+COm4C+4AN3JPxWb4KPYHB/DoZiGI/EJtOBCTMJFmIKLcS0NIp8bmG4RXlxMDSUyiDziJtGBmy6GEUv5+zYilwsrOVx0CeBh4mifCk5LiYNE4JMuTmcwxEI6jCaNNzdCeXAjl8XCPIlcwpffg/n8BPNJwoqzKzg1Jo7y/1PEctL5ziZ9P+ZNXOezbDxKRPJ5Kvlc4P/uHSs4ZTKta3/y4P9t0IdYzjQbmSYLCwjvjpSJz50SSEMk839PHMbnscQFypGGGUQ2kcnfhyWw/JjXkWUjj9QE5qVMy2fuA5gmgTogThG3CJ9ElokI4m9JxHWmXYtLE1k+bozKGkD5MDuReTA/N25gCeL3XhhCJHdi+ZimkCii7A2SSMtnSfxtLeGbxLITTr7Mi889MDWJPIgcJS0xzJf0uCuJ+sd8rNOZ9elL3piGl5NIj0H8fhAjMYlozEHXGV/KTWR3Zn5E5ByWD29tJ6851A9xqzPzxwYDmT/2wsZeBF/sunJTZDC/WwifuUyzg7ZDhMxFL9Lz+eK5rBvCx4vPiV6kCSLy+CyW3wczfRo6zaOcSh7ENi/qBPPQexDtRkmLQTuYzzwkLDtYNi/mP4/0/C2TyKXeNs4jHf8/T6TtoIx+LIMXZdjBfObxOdO4dWH+86gjP/6eTPugPG34rEMy88ZIIpVYTuwigvj8IA5jerc8F6cT/H8=
*/