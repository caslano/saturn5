//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP
#define BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators pointing to the first position where the
/// range [\p first1, \p last1) and the range starting at \p first2
/// differ.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    ::boost::compute::equal_to<value_type> op;

    InputIterator2 last2 = first2 + std::distance(first1, last1);

    InputIterator1 iter =
        boost::get<0>(
            ::boost::compute::find(
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(first1, first2)
                    ),
                    detail::unpack(op)
                ),
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(last1, last2)
                    ),
                    detail::unpack(op)
                ),
                false,
                queue
            ).base().get_iterator_tuple()
        );

    return std::make_pair(iter, first2 + std::distance(first1, iter));
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         InputIterator2 last2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) < std::distance(first2, last2)){
        return ::boost::compute::mismatch(first1, last1, first2, queue);
    }
    else {
        return ::boost::compute::mismatch(
            first1, first1 + std::distance(first2, last2), first2, queue
        );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

/* mismatch.hpp
yLHLJLOAJnwGDCB1lZmAOd1WzvWQE8vLiVU6ciLnI+dDYn6AuF4L7cZnVlaMFgiBwLm4fEJp4bdpgDvB02XO2NITsLM7JUwGZDPXhtAnMqJGB6Jww0ooKvdSA7joVS263BNLQr+63IVbtSsN360EvS6DOBpu1cYZWTCc+zuEoQWD4cVHYWceUsfGok6QNWJvdkgoYYxggD6G4oiNw/wMAzcmSXto9ghWXjl90EiDc8gm8ydxvgG5BBZW9ql3BqYvUydkph8xWgRKmFR4C8JUoenCWh2/DblkavRFyOTrt5lbaQFffwDnUSI6PyuXSDaEpVMbj88oOA2nPSi2Y+qSLbR+hZikzEE6wyO34egtmoVbeTU0gRjlZMdi/TZtnFhrKBxZo/By7HoSjjbNmt+NrEnVx/pz4EWbUiNKvyVJa6QahbsuUrzGmpEHMfsfAL0FqYCoZkxCtqPwP03/YrWhu4Lq/hKKRXLmlcklCv0pVURRYl6KYpZah6WIDnwxb9l0BHLdvlLJku4EYkedYihmMfm/jicjjMA2v3J6lsRyQU85Q3uKTUNmLeCseklyUxYDV7/UzNBGnJ1F3BYI1plKoENnBLs/xn/zMrH/m2PTPG9jwWGxaS58UD3EmEH0m7ilDxf7xi0vifeSLb34PhbEyHwqk7o0FnXlaPl8102fG6ncLZzINkrFNDZ/EhiXKyB7VH9AJoJ2Qmx2AZwQn1wh5hkaSssQHqmbsIovTR9E3RC3X1gls5hERf7v1iH5MBhPRlhOtObgdiyIjDYKFciFIfeawodJw5wo4/nUEUPIajHuvEtYrSvwbWxALbSQzEIh/uCtiPzjh7TiVa8XegiwWeJQAAwUd2jPKCEegDpGnlHpWJi6MV0Qe95MbSPZSbmy52doHu6gjtKCTCxaLCXm7UExKrF4D3XhDCPPn7tzAKRTD+tHbi73Y9LDvwLNRS6qUpBhHeVf/rn5ymRvFeaPpQQv1KLXEfBKzP2o6jRQHnClCoDPmeX5v342YIShWGrHAKBjmotsMVdYwV546Gs4WudF6HeaM+/phWELGgxcF+isHgSafbiF59FwuzJiBeDRahD/eyMSiSkseIKkYGZraTGlQixWA6y1xVAm4tDVemYH3r5hA9IyEpoyrb0qeWAlnQABaDJ106tShXj1oJBS/KrkE6/FIJ2kRr0qgViiXg4zRzFlOAlX1SzYSfLII9Oy2IH8dhZLDVlszpne4wjZimkX6iPZO/wo900zVRGTR3Rm7wBEAmMqgtVl5ZsgJ0TMKc/iIahjlvjfCdSCouneuC8C+kwx8Iw5pphnqpubbULd9GWkY1DvUBau1oP9enAwHnRVR5wKP/OQlGF11dWIVvzYgwDaCkcsmXfIWmfCQfY1dtT4vhAi4AGFCNbP8uB5QxMkAt1xxQwD1GqA/5TU5bE9XtRe4Y0NR2KDoi1OS3emc1xqNRu+mdLY8G0k9uIjNbmOmqRNBhtsK8HDq9vY8FYqVwzlZB8bvkPUlkvapCLAutRdQn7GBvlFG+wUDXZlGuwe0mBPpkEFGblcuqhNmgBPAM4SichhFmkJmUsJi4DsPhwYNKhpPS+z2mLasALYrMsaH+6hLYNpFeqLeq4L8YZ/1cIr1wV6riuj5+7/KiGX1xpVMS4XP/RPlNvYUSiqflk0KvpQ+LMXaTWLTI+3aGEPlV7yX8aQFj5woLd+NRvBiTDPtcMi0zYAeL80hCZnsrtFdmt2NlJalzoSiANV0y4jdTLlxgRTv+yj8q60ZAICai5f9N0B42yFF5p1WMxsOOqEQDBzt2yjGmm6VTqEbrGRSLlqFD3YDTKj8ewEwBU2o+pGXx/QiPEx7lGvjPEJqudGNEdp9W0yd8BDagw85OKDBx7y8CEfHnBeKKnGlnYBD4+vKLLk2U4FaRdQsikovYL+SCK/xg2thz/4APKKbmYDYtdjbJiSgxvYlOMO/BYJkFOKtRtozChJjDkPKvX8v4FKDWQ/D8RIwG9lvN+YBWDwELYrExAiV8udKbse7RRJEzO5FSK3C3O7YgeLUP9viZyH/7IUf1DWO3j+XQ6TzvqTAKuA3GmpqAG5a0uPWA1c42qyGWCVc6plKOngH80GRf1mGGmakoBQ44qtqZfYJywPaJlTLTE2ELjpDTdq6ZA3hEQqT6RmySGx3iJcstgT0JKdoKwWWrYakMuhLgJ6dWpWPMopKR7sr26Jyb0FqBkuAAAs/9MH+mYH/bUXWQMsCjAaPrRihAxFyGUP85//JB+V5TQ1ZLY6YzONOf2Go4xMTczGhUn2wMIATtW56hPVhSCU6/IRPuaHKJm5m38FlI9QokOo4rz7ZgeSzsuJrSlT4dEtHsdD8aZGJLLWqzYuXUgzy+NCmuUnYHkFNbtp299Dme8mQzsSDyb5zCDaU3DJhNUlLncomH5r1FqnJL8FyqRmiYYmko6e7mlMpqcR2Rs/5comGix4BNvlt0yGBn9zALYA4VSLiU8vtIzy4PRbIcNvBGiE6tdpgO385TutAbbJg8gZIDHwlseG7Bp3g8YBAbReQ+umt27+14etkbfzKFRO3cO0I/X1e8jkdeP2AQMgXt4GFCEYR5GpB/BI6zZbHBmXkwqf/AplYNPuuJxQ+DhKwD6gib9twZcj8NQNEhN/9P8y+Ev8A+lrmrXLk7JUCMH6u7JZ/7hJ2ZQxhJLaJ4hmeQLv8T0vC9czKL6l05K7SAz4YGK2KjltIsj1zoYFlqQ/x5T0tdsB9arUqVXqzVVqaZV6ZZXqrVILqrTbE+++dlxKrUw8+nK3lHo40bjzgJSqTzyyZ76U+kbi879eIaXuTvxr9y1SqiZhbN4spe6khqZXqbdUqTdWqddUqWOqVHeVmgtkKPWVhCEZUqo0IYEYlboa/sDb5Qn4lVKjEgb+cSUMkLBSuVBSyqjHF1Je2MQek0h2krzITRoJ+K7OiWudF9WGTURlhIBkNRNIaOHvUC7PQ8LK9KI/LdXBHBbwZTuRrrqyoO0/FAh6oR6x4toiPScQ9KiuAMjwIyk/5aYmIcGkesBsdVu2ifnubqTKTkAIKYMQ1o78Sojsn7dfuB89Cqb/6vGMgfmnUCaj3lt7DHj9ezcPGvwP0ElWn3/7qMDa9IAu6leqsYXZ1MvmL/Rye1Yv07GXwgt6UfgK7ON+0YcpGNaEAMI/HeVBlTSjLyN9jNjxOZLjPxnW6/rRZP2TJZKU0XSxTI0oYhV4cokk6KkvI10CwWfnkDVNQTlSeCuQiqQKBccCdNjSLhb1gKmRWhgVdUnqJbGoVyLFTxULgzqiP5ktj1iOljQDmRgPHuFd3zpvkKB9ROG5T5xHC5ig8yFgULPnNh9yN/0OZdVKB4zLrhjHWSX6jhyKEZrLKl2ZR2/m0ZN5LMo8FmcefZnHksxjaeZxfOZxQuZxYuZxSuZxauaxIvM4M/NYZT0u3J9R4Z2B6Q71xrT5yTdUwNuyy6RgJNt9cwJZBhdmmYKK2e2OWDvAQ/MKRRIoGLLMIvzxVRuFOwBZ0vZpAL+x3GUsh1+HMcF4xGEULtsyKiPwAaxjDUC7boh4jJVF8Uqvwudtgr06u4gdt79ze3xmx+lVI1jIo3v0Sg9IY7c//ilBGSj8A0+BSunUZyOh1KscoG7rTqPSlaGioAGgny+pDiNfXzmWr3WyOUU1Z98BYaRTD3rO7LOp10OJO982DMNd/tGKHDYAzbGze/9mD6Fy5n1x0LBpnrKPtA9S10HBa/5bwY+vGLAKkh3VpC2wfcL8+Jeh50k9C2Efj93+CtCwfj062HxGvZY1OI3HfGwyv6aLfHUj6ptBqIzAv5Bs/LH5jPYBg5KGehWbhZhTpPBzJy9WUvgFU7eQU/BW4RSUfuj18N9+N+0UvBydgr9NV7cN7eh3vHiT2Jv7+ci15B8MiTFDizeE0yN9XDQwiupOKjkKUgC0ULgKUAda6VxkYhrpncImwM7V7PEtL/SE9Gg/UH5+3XeFB8vd/AlsL2MF1PZAbYV/+ucBQwnx/HT+ccivV9G+dZj/cQNM5DD0XJx2bJh+M1B6J4BMfuotLF2/tNDDf7qBbGE3xd4SFiJQrOaihngre3EbJMQGDGAbYwWPHQQK5VP4C2WDRmq18KUd5veJBq6OveUcjg0UGZPuRMMGlGTyIKJy4RHA8tQdsbfQwyHtKSKjzR7FLGRJPWj7BCLpg25CCv/1DweMVBEQuGB/ltsPpP5BYHrFRBbHp83FISHgg2iwzIbaq7u5EgVCStkFTwDJVyW3JLmbvgxvaFAOGyucRuFzmwG/Xm8kYUuXe0l9Lj9rMkRd7ie1mhKE9gppoJsOjpOozdPqZUDaDK2/rNLBDlcpEVs4zJ8D2FCRHCziUQshH2hhWV7EVqWEwwCvR60SDizRp45GqabSRY0oESNsrHTy2VYZJw3eLIOtGFWKsdLFDof5DViG3Fgb2mnW2vXpUjbRVT4UyfSPA4TET28YNALR02qOkReIelS7UekIRPvg72xnIDqIf2FOvaY0vWjBwkMZc0sJafrOeNBTnV7XNPUaYrYXTgpjUvEeofoaK8ziTC4y/QroAUH4CrUvljwPUk2fabgvorkNkjYqrEt/345CiDfLYcO0Un8SvTZAndW5gVwU8LQ7A7ko32kzsw0uWnG2aUMbId7WC2PM5ej+owTL3eMUCJxyAh2wszWO8JAJEMEqsRg+WXxAUo/61FFi41DhlWZh5OpUPZJLOzo6yH9+jyRh8RsgmR0NREsusLi6si2sCh9xwyAZGUusNZhrrYHrImuAlKREWKGiyCftoMABe/JmRoSGy5s3o9xehBZSL4wQ5aXgD9Hk6TFNnj7IQF2iyNCKufS8MHcO/nggeyRof8V1gGm4m74rob9DIEgGVEOZJa580MuCHjZpFey7Kl0uevt26W4pXLYXMHN6NXJHqPkuk71lsisM+GqyTJFYVCZ7wgqqnh7kpiLRxYJeKFnWDrWLKqjnd8kKsmghCmxzhwyHjFILslQMAUvNOWTJYNDnM4PGWZL5CWgAOqwsXr/x2mxtJdZbfIFfnEiMwAfLUZeF4ekh+c/E5R4lRI1azrpzsWS+UqNrPbrGefRudJH6LIdmxp51WOH/vi7L+tr2apYTCwWPoNP/jjDMjIzxCtUtbDKTI/a7U3b/O7edlX0S0Cg178nfI6miV4d4hW0wB0VXgAGKIB2EYD4p4kk8gXr7j0+Q6A5kyihshYX0G6zT1FQXk+A+MG3IwQTyAQV7FUT+fz/oIOT3COHYZTqVU7m4D7zpOUYMksF/92BGBt8NjabuvcgWS2uRtC4fXTtIm7F4aAdD7HYjsbPRFzHO/QQq43r4k4FosR7tcW9M6lFOTYdD/NN5yFJqyGrEHz1Bh1qG7klE1uUZOidMq2jC9GaZh4HxO/xGys4aHJEio7AdypLiGhb1LqLLXHLt/8Mhnr+NE76xtEvaFXuTGDqMSyNd9BoTeNnEOxYtTZ9F4aQOjM9oAgl0zKBnJiE4dgI5NlSlcTySJj3WHkCHiexUR0bckYI0dZrXIpDHBNSdFyVeaS+3F4UgNuMe2EVopXkJu5/hYBVO1rjNLpGVcKLpxEBCnceeREMJq5nLgr022FoTC+yahx0s21e2l85YPI6QHgEJe8tmzIUU1n/cYMAPD5bNmFcm94kyebGlLill14GY4Hk3WJ13YHUUB5sxL2JHyQ2269yyPpA8yjSX/VwoPMcorG8hRoAugUhpYhNui0+OCzsjUsQTiq518V/WIvQ9JtjJzNNyvdyDpp4sAhDQitQ7auLBE3z/Vx2gEIYihq4NMq3LPPFDx31OtPDOWbirSOM+bDnFuvi/rrFO+5zgP4T6SFCOKCBkd+naEaCTutZRw6eEJImfOE7HgCJzE3/E4d6GwwVhq84J/ck7BKHW6xICwYBAxOV2/yG9ql+vGtRRZYglPV9//GOiZmiTa6GnJB0agR23A9hJsIjtBSJNUC1r14NHpuvBE6nLgERjuiud3g7pHSbFuBlmvo0fClyEYmwjirH3fosGbONvQrHUuCwasOIiNOAwP/klFJ6KWV/sb3b/oVi3Z3Z5m3vjXv/JQN0O2tX79eiuNrk7H3CnTebD6E8vHSEMboc5xe/5oNsyRXzN0BLxYCu/DrpOW91ay7VdlmML2CQNHAQ3XpgeaysfjmMtZcEElh0xhP4M8WyG+XgYbmzpZim2dKsUlzcD19seNvzQL2+cCyK/vCu23xFrg626K8e9fgloVHxYByylDzFPQrvGY8eIIIdQT3974wCsZLffAALpA/jp0W6YMlAxPdprFKrEhnuul2F/d18vc3aUMrv5DSARQPXm5OPDTCdtxmwpTi50Kzx2tUWHui39t9eEO1q0j/B7r7aQ8Qh/GgbCF8PIMgc+Li65mOSjhogjMBU2jYBDrIV1wjo2JxsKgQiFgcPb96JMUI3WSx/yPl/zIcgDucCOAoAX6CC6XkdCXixaIjVcBqIEVqN0Dx5x4P+5CvNKKa8ojHp5mVxq1nsf8iwCT1Je6f+voHARD9M3fNkepv9XgTgjIlS1GPJpQwbNr49cPemDLE7fhYef/EkguLaIGw9kOprRzaKkJQskuigY+JMgGlQs4D/fknWm7r+tQ3rQRVmDhkUpZu+TVz+sB3lgrZIvDgGkp2HxgdQ3AOHYNFROQZOCCYB+BBqU8Z7CZx1B5OqFzkB7XY7sa6UP078C6WylL5KDmSHKbUSF31JZuXBr00E88qJass7JzeLgkUV6Vx7BU5OuzMxWFJlW9WA3TlEcS+wy4W25CdRbgEoi3bxj0kUPWnZblHfhbda2PsEnQ1kWWwKj8R8KDPeBqqEO879Tvtf93D6272xnvPbInOorkkD7gMRB77Fue3UsOUJBUv2aIkmmrbpL7Bl+05WDBi8/QmbziCtxI+7misPER4gdk8sKYMkX2/NRVxkffyaBDM9Gbgx1rBC4iR+nSWGSVNe+1FS20tV8Rp0EBJbz+okXnaI4Sctb+BPTrSlyXgNls03zh/nTY7MFEJSnTCJh5kfGIsHt43Uw9PThnKEiMWyz4ho7yES4C5DjeIbKM3O/MI8hPTihh8wBhojNfyYktkInKVk9ZF7tVUKW2Fx5F9BpIVl7MqkT7spCouc3iU0RqUosRrjf9HtCIjxuarqjtF386TXkjmp6D+n+b06Quwa4Hw0OQGfhGcj1O5jcgacnuwOTiLGVGdqueDDB/3kzsDZtByy3MamX+FoChINBfupePLucOHVF2nOFniM548T6KjWwnf8CGsAD0KH0+ecOWrXtJjtq4Xtuxaa2o8n4+1A4dZllgOkApWJXeovDKFhwlxiLwl+/YtA49TYi02HeNJp8azPFkZElwpgwOcu99n20PQlcM6eMbYjGW1qyEC+1IuOfW5qZy92BXALK1BDO6ORNDslqJ2IIsLQIHoKTyqFJHfoGTQqRku+9CWdFVZLYdbIFNtSuFq6PsKGzl59rFzvIk9iIK3m+jfih0MpnBaKl2m2mtDEO+u/hC25COctcDjL396CkEaYee1KPWODzZGh9ailpNlfflJECZI/Z6Chsy1Jy+EhoJVVmqZ4ZpTL8hW3X28IdX8Mue2mSXRMcEr8CZzIhzXaKLbbjyWY7Wy3Z
*/