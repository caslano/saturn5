/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_10022005_1838)
#define FUSION_INSERT_RANGE_10022005_1838

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_range_impl;

    template <>
    struct insert_range_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename Range>
        struct apply
        {
            typedef typename
                fusion::result_of::insert_range<Sequence, Pos, Range>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert_range.hpp
4OM9y3K+r+P8P8cysr+DX3QLy8k+D2mLctzvIb+FKMd9n/RVB0OWWsSeMUrX3J1mxw+npwyTu8HPkszB8SP+oCLvyxnd/Zz1whdCndZxRBrmpe5uyPMpxbvBLgcxxsXDzGY0HIpL5KX3dcGUDvpbW+z/9EOdzhCunKbXgEU8AxmPKy/O891wXut6VzGM3zCnvfj9tDjC7TO5/k7sqUp7P7Obo1l/toPb8vZolv5ZxRyneIORXBo9PwrA7SZSBtndFvQTN7Thplvi7ul/cVblK1fegeP1mK1R4fkChT3dKM75wgS3MZJrLyzVON7BSM4tQQk/fASXnbq5PsbFkRzVihwT4xydp1jOvmePMG8SZz1Xxdr/wJa1PFeZ/6LV/Z5NFeUr64vsp0wnGaap93dbrTKu7W9pzhdDDW05CIfazwqdclg9V0dg/C3+r+7E0tK+YDd2ZmkvgNfTc98J2FN6bW87DGu1QQufBFGxwuf9bsC45iPfJf5eRG/zunxzi3Vvd3x29xOs4XWNNsUv7/GJOvM2yHeqLibaBXVj7nX0RKQtubjSqU0TIPTNm2g9NV3uL+e/dmWru4jk2bGQkfXBb3lSYTOXbhPzGw1dmUdSYMM/V3+vraGQ9N255JchR8d/0a8xt/2JkGvSGvewxsjqxBmm3wmOqsNl2bf/RYwlv48w1FQV848YQ01UMLlLiDqg6qHlb3ruhrbhicFeiCgfb69ch1e8itKaC23yvEVePsW/TbO7sN45mTZSjHmGad7af8MWTOEzlqESVndc8/9SDJ1uTG6NtvhrqS3WymnlVGFnohz8aSzV35QupfX1piO43+p/jsOnetA5FeVR+rziZG5rGIssw7mVe6k5TlP26jolCuVR+PNVM7181yOH94j7sDSXvoLX9sFVwboQa9pNkXG/gJl0F63sHiDicfIlUb08e6fxPTKc/k/OD46qZVi2ct2/8FOr06fteS/itxG9nVYu2u/3JaPfK5v/gdEK7mJ1oyXeE/ulZE5Vl9JULmO9ROT1dODZoU7/eH7B+BQC4/aR3NbXKc34xufmZoY3EFL/D/HlQubE5MzU4fOI4nM8ecFMTB3B/TXU3wGju0h43DG/1+e2u0KnWe7MeSUfQcJpKB2wjLzHMrBh6O/A3E7p7oEVerIO8fDZ6wNxTr7pVIyHpe/NKOYE3S4p2bsjBywjfZxeLAyKRO6N9UvXAuNeG6LdyPHpifIs1eL4Uf62QBP3qCnM0bz+bvT2bXZiXRUzm7/9TiwlWvZbzNJUj/ZQy7gvxOPlY6LMsjcpXpveH+UocbyH0Y3Hp+/CxeMj2+T+oy/CcaY0OaHtIDkQ6toOkjuEur6bWgj1GVEwcq3scZaThSPHiK39cZYSVkBbjcer2nPp8XGGCoht7C5xxr+Fsoz5VhCfNhDmCkF5SiOR4W2NDI9yQBzOCh9mjsaodNq2sjhMn3t61J9PbCKdmt/jeW9VvF9cPKK4DKPDkh3yftLJF8b2ONteo7grC80Efcx0jFvv1IRPW3oiGExbVpboopLc13lSwNDMDX1dV2utGr0FvJI6bCiDUUx6boL3np6iOT6az/OdzWnL1GTW6D989jXCtvjucuEZrLt8U9NprHnKJy2B3TKLSpFniuafKfQOFZA8v1hizblME+nbR7y3d2+tZw+UYVyqaT09YcN6qa719KszYs70Ctb9jCFBn3s/aGmb9KWAAm0n/E7bHQW73kT4G6/hv/tZBpfL61hb8vlCujg89E9oC6+Hxvc0aMVVfVeqpRhOMzEYqzST3VRaqFNzoGIapgft4b+UXQdwW00RFj+9m95BEDoMOKZ3KbacCGRLWHYgNMmxlETEtoQ=
*/