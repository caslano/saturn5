// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

#include <cstddef>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Box, std::size_t I>
struct has_valid_corners
{
    template <typename VisitPolicy>
    static inline bool apply(Box const& box, VisitPolicy& visitor)
    {
        if (math::equals(geometry::get<geometry::min_corner, I-1>(box),
                         geometry::get<geometry::max_corner, I-1>(box)))
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }
        else if (geometry::get<geometry::min_corner, I-1>(box)
                 >
                 geometry::get<geometry::max_corner, I-1>(box))
        {
            return visitor.template apply<failure_wrong_corner_order>();
        }
        return has_valid_corners<Box, I-1>::apply(box, visitor);
    }
};


template <typename Box>
struct has_valid_corners<Box, 0>
{
    template <typename VisitPolicy>
    static inline bool apply(Box const&, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};


template <typename Box>
struct is_valid_box
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Box const& box, VisitPolicy& visitor, Strategy const&)
    {
        return
            ! has_invalid_coordinate<Box>::apply(box, visitor)
            &&
            has_valid_corners<Box, dimension<Box>::value>::apply(box, visitor);
    }
};

}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A box is always simple
// A box is a Polygon, and it satisfies the conditions for Polygon validity.
//
// The only thing we have to check is whether the max corner lies in
// the upper-right quadrant as defined by the min corner
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Box>
struct is_valid<Box, box_tag>
    : detail::is_valid::is_valid_box<Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_BOX_HPP

/* box.hpp
YNXiPdFRR7YUP4c2jcgbUSi8csKg+eYmbUScaXyeDV/HwjvAPYrxLMATQI7JvlYrOaGMjz6cMxQIJScwepVCxSnXGNVY9fMCLT6S/1iyGOaOM3/wZTFzvmv8pclDRSj68+HhXTKAQukSz28LFnMXNrV7+KILNBvML3m7xJZbksLvZXl1dLYxUOR33o1ogVdHS3qfwb80noJtMcz+UpUd/lEn9qGdDJhSOvnVNcN2grHvN8DSBQUJLPmRJIFZiPJ7RRo7/punKEB/UUpxcHzzrxfjb2YN++Z/PTPMmzJnZNPRcFCkIKgPyNmU2NnYEDvPrG1B4ID0pw7FMyLUu/AmPaXBnEtsS5IDoGGzZfCjuTjDwckKBBQ9Ojvl+4NSEDmvKz4JTg+AU8Kr/q44OGHU3vkBZQKBdYMAa64B1t/GsyEA8eS3YDTqX7Hzz/ji3FQcq7eTVKuO4LPhDox9Z+29b4Yr+M9eIJvlrXCF2+A76j+eR8ixXkridZAfuUg5jEfDqYDGDDOSTCvrXDKoEGxSD3+8OrmHkqQeXnueeliR2sOJf9zDk2+QebDpfcXCdu1m2uuC20lna9sHFVVKOWspFQx658R3EzuSODtvZPv5y2hxxfpk17AiF/qiVpujJSdL4TBtwYIEmKyoQOw+Qb5e2yg28SWo9E0U4y7W8OakNSSSbx1EnP/byC8hiPNPrro09ceE4n7Z7ozB7ZaLQlsivF3WWIN+HEDR13bidqvgE942Uqjx2f+gm0sO/4XkbmRKFjM0qm/CO/zklZdudxK065Xt3mqcXPZE08Gkpg+nNI13+JNXDq2QEM8yki/bvS4ly0hShQSRZUQUMZhzZUqFhGjzoRQ3t0yjb329cJxUp4X+ic4mDd/ZRznxztYihzEkBeWdP04Kva5M6A+CqaHXVUb6EBs74hEeam+LlCWe9p5CrLVKHJzvIEhTWCv4DVHDDYS6gh7M/SaLnORGLrpXfFW5I3JxpKNRw2iPi6OVCZGLwONELl6ngvCf62gsspLj13UgfPTcZiWDEflW99xkRVkdnnDDl55sfKwzwic6GpEmBRyN09Loz0Tx68Y0+XSfBdHvv2b307gxhKKC3wACJrkZ6IaPzCGLcCH/Y1KM3AeXipErFg41TdeglEzmqVw+6jkLlqi7Ho0BMOQwxVJVvYhJo8O3UXxH6ZmvAtt+c0F4hW/mmdXfe9xqa5lNrreuYOds90QTiLxXvhl27BTRO27lOjK2FLtr9ejMXr7HclqfYzhdz8OAeqzxKPYaZkZDh75sA1b0Fqr50Tr0OLzZg9rhqpApYw0/kXZa5x2Xj0apFeFjNictXzBJEpgtrqILdQA6mBr/KbKqCZ68oABtTk9hgqxqt0ivVivTq/XUGUuANRUiFyc6mtAzNEIh4CCFE1NGbQIdHYvt1gi0GQGSMPAzuhAVqL0ckCuCfPcLY03BqsCdn4T5m89K00JOk67OBKF94Nvn0dp9G2MkmJbeSk1d4d2wJQPw1AGn4pY3MtCXkGfWXKDQtGoTX1J1Xu8JoQWKCUncd9DR+GPSEm2hMdpJE5WnjIxcvN7RdJHm/YY0tPWaZGmDT+MKbbx8xLiMG7tUGEJszxoVed42mWRkUVCEohQE2f7N/MdjyMHfnadOQ7OkT3EXO9Y9EW9XqrftCTV4GuvnC38z1uTrr38wX3GXx66D98rhvdmrFwx5p6m9oQgeWsg6ASTTq81YMAGL24u5GEJ/sTtQGpcs2NxK2Yy5VLa0CVry9GFQE+VJE/6j0404EBH2vB++Kvw6Ozk/5wQrKoTsh34uiYB+LJu0GU0Pgc287PsX9MiePAzKRZ2icg0qAggSbL+awe2YZXcEv1zEC2aL3QA98cijF/TY+MjFLytj5PqMdDT9BoN09vMPLeJpDybEyXY0bkoz0NWHdQcboyhL9/k6lYC3tkbJ1GprDNSukMIbPeytrcWbtUk318X3ilFeUqP5eae+8MdPwjKJp0CQTqXOuzxXWcGwBlsnLniB9L8q0NBnt9g9G1WDlKqFwHsIDgDH9nJ3nmM7WhUJjZm544/OUR/M09cTrR8iOqM6kcRqQKPqgYqqEWvQflJ3JTn9wvzF6Fg6OYoIfZGMi7ZhLcGaUYapmHLwDTc/o09HY8icshdvfw73IlVevfEpuRfRMth4C/bS1juG9g9lGaNBIA8kYOBp3zwkGBp+B5O2u5JDFbWKMW509VyMdIBv5Y4opmrqoZTlAjxPHgZMm8U/G3cWd3Q27OisNef1wR1uNppqWEi2XpgaF+dlW+ybyS19lW9KtLRv9fAt0VDqM42WThgt5aTspqRapaQVbsGyIEDnsqUyxCzyGujrRTXROWQ5djT+LU5ZEZRIWKQw0bk+y8R6Acp4hvU5Gt+NKwAELPvTWSW1vps9Tyt1FPjTBa5E9ku44CgzVCmOxup+2CJFBUbGWRjoIKod+17iTPm2JKbWSbShcjFlrCSoI4FJ3svvvJ9IqZuZUTaVMEJnXPpHtVtpYgr6KObyab8ai0N10o98+AFNXJmOfiNzWBd6FqbmZgh63uVtTw/NzYAJFk95joa8GwWRpmhYkokalmHVvY8TWeOi75GqV1jrNghz/kFe8YThvnIQeHQ+5wmUD9QJXv+AepWXjF5KpvBzrZUnPSZQKRRt1r0Q58emD6uOFC3v572tJHaMEZkTRUvqXQaHtieFq7tJtjIxhaurHY6rW7BvN09zpNrvyqhwMO3skKORKq7RG7GvQdsVsu17EiMkOOzn97QacNiPcLiLBqxejXC43BtBOKipo1e+tvKnsuVpvH7MaGCZwmdl838dAoC/RocBwK1fW/mObOJaePst+fbPUyauiGdHfG3lMTnlpJRbIcMIxY+eSac8TATG65v6wh6Zfys/nn8LWzspapASCD9aYhh5Fy/QN+Ed/ovRg4DpOQrg9C6yKyNAfomls6LKfDQxDvh2K9/Fyza6MoAWR5tWVClRrzwE4vu9UjYvGYJzf1yXhHM2/t/wEzU8qhVzxevqQKQLGJKQsEoamPZTUp7bTDwzMcS18gww704ixv/xNOylNUhihnD4L96SxOEPYuuXSrb+FGtF3PEc9e0nmS1i0yMBq96DVFI407phuOIhqol0X/1pnfWjdbCYt7ZlmliXttBdxevL+vUgXXT/eyZWFJIV4SdRRfgS+2hT3IeW2oqWk1fLZGY2kuqYUm644zciO4VLbIGVfNNFAV8X/MvGQhOO1lNE6cLPS/A/LcAftW5g0ww3dYU80wOlCfd1+ok13YW3ulwdPo0JZ5/1cQegg9xN15Q70Wk4yaO8NdmxzCIiaVyrvz70OgbkxWYJz8iJfPHMZJfIaJ3JTowg39UW9yafJnvKpp6o7hNczZWY4VjnEAa6SQTtN3+cScki4Hl3A/pOudHPzEdv0+mj2oBzqtK1dOkDjxkgA1i0Qyuy8pLt8DZWjV2amig/heZS4Ya1HVI2DeYuurQG4gtF+IWXFOHxDr/hsngxjWltz7/wcZjvfh0wb5EN0wcfbjqqpkc3thnGBCo1pvmP4WFGXqGthlKmjP/lFJxMJcd410CmLCfm72bNAVHCSfWS8c/xbDvVeNg2EqvM8vXfF0hd0s5/+YtMMhiyLv7vQcRpuFb6GoCp39MOUiK+p+wV3UX97UGe/RH0dnkQv6OxYBI14oIXqJoPfO+BBmE4WAqMsqVjMvTNPPtnmaLQGP+3iVSfdYdHl9ZCyuykHoYDcufN6DWLySexMW0j7nLm59ryAm99two06Di7PBQK6epJdiCoq8f0p7C6FrJ3sZVUGSALIBhfLam3Ui2e9t09956+oCdUEaHBuoirGalKxSrpwWlJJrnb/gmdxJThdRJFtv+j9qfykqiDd/hfMlLapYKu/DpUrtXbWK/voqI29cEGTo/cX2sih2jidj3t3qIaYE/QyqMV1ehPIZPs3ZqSZjJR3KtJV27BBItFFUDFV9RoKwyeOaMCyQrJDsQ3kGggMzsO0i+nusiIVNFHDOfDHc2i0iJV1gKpob6bkIWTkEiMr/+k13+sfkS+/1hsFPOf8fpPNITy0fNFCQrB7vZzJARh6Y9kky61wafC1QRjSgIehb+HXSbFCTLy8sokYS/uB+N5fLDKUdjs2RERmRAtrNvMpiLWBPUP4Dqs+kiR9k2bY42nZBJXyT9zjh3LQiQDpoL1dqVjhlf+/a8P6IsHF+lgc3LOHoJz6uDrZuVa/RE7d6B15BFrbIynPXqPLVTAH1VhC97W1Kf+JeYu4268jc4BV3jaQwXREhv/JtxHBf2fLreZ5qo9C5YMLR0hB3Bu/oB+6ZzmrCPSthTJpDqKPwVtwqzSChL1K8p74vngbW13LgEC9sQrWbKaj+up8xgqXz/QlV4Tw0zja0ZTpnP6bKHPdfS5nj6foc8N9PnCaNyHr9P3TfT5Knzy55rHmrqa8fKOxYA/izBhu5loIyby/mVjFogPmKGeP9ZIIlqzC8Qy5iyDo2deNqDbfSOQO8aL2kY3fm4hYYiueI5624RVQPz2/aFurm8Dbc1CtkZszQ0kFR+Ov1MoHqj7rfjJ1lDiM/Kv0Jpzx1C+9AdfIXLE77QOqsZ1ir8y4guzydva5ryNxSheNgB6cP2/GqCBpmSAUiEAKkB0doIsBnASK2j7DiojQyF+2aZ4+Wwz1nTFKfNMq7CJHhDWfq6K7PkqDNpwg6h2tdlwIupLxkTS/+UTWd04/ERuHjyRy3CQZXIm8VkUWzBzejcpeuqPafVcqz+h1R/HqiP+7iC8auHKk0BnSmwhvMDLl5/W0Tr9GHry+rv5idoLePSsfilx9MDy2XA/rN4kZn2SO5/4V89aiyTPWq7LTprR93EdgI8wNseP1mYBTk5O7IdpjH5pW7DckPxe3+tt4/CzYaWu9rJWvMZ3vAdT6zakiApNyvGHRfSYP55xmMQDX1ddjTToLosbmJmzAnm/w2Qypvz5wlB7UPf3io5ZSa+vBTuuewz95poRGMzv1JoRHvKR1F01bhPhF+emwaUh0VehxCkfpNXtal44WiZeS9rvWsDNWvFLdVqlNjMovmszy8UXPvrHOibMZwW2yH02DJt/oCxESZfD9/n21n+DbllZbkscwNPXwDr3s4wyPA8pm4D42m2S52XXnIXmOOhELyLXNOblB7gU2Lx+W93zSxYI14Qx8ZkZhGDqRmP/dK77V2PSXWuH3z9/uXoYQmB+YdD2GS1KQ6zZmMiJTy4jeFO4jKQL0APG0OJGm3Fknn1BbSchXqsYbh5+3zmJPqeMId0enNueds++Aq0V5xjZp2vNlD61uYbeWEifS+lzGX0SXd+ZS5+VYvr4/M4q+l5Ln2H6VOizDgfyPutYov2A4NdMUGlFqMhjuXpS23dAquR5PwL4H9EWdXdZEOrAFmnqAIvQ4YFzzGMMuwUgjfGuJa1ReoiPKoftw1ziejolSbeyCE4a1ePk1z/MW78rw7cmD3qLnutSHopuQW22905lGf+3DwfwSF7A0rU2CrhoowCq2uJo/TFS4G3Fl6JvYrRotH4vXfIfrjZrfl5tjvqPBWXZImrb4J1KjiUU42gyQkApN7Cpte99EvadVSboj7h4ZSPptrLIYFsrHZdC/OaG83qUIR5R4YTr/jqWZAJgxeax8zpf8YKBIW3tn6VUvpL2ueTUyJMT9rm8VEG+wCjAjNqQqlHo3+owkw4+L6gvdxkJwKWufrpQsJahcy8/+HomqucDYsb8l4VChM/h33iORPhOIcI7fQdAUnp8wG6Si9WpTIiGXZiRnmD4PNEki4j93q8Hs2OPeLfiKisPCYxgLBvxKDDN+IkKV5Dz87RApcAHEPbhd848jFSUF7AmHPxehvWfr6BOr2AtiBM+ekBqIRdWAnJQq1rtNCNvKn9pQybawQKYBTabV8E0UfeeqmHM87zLK1aLwsKp3n2luF9bjf16ULnR+xZl+/4SwNQW5M9jIoRpQPGq0xA4QqlRfXF+/l7LOW+9rcGCPCtQbiJES7Rm3EmLh4+Vzj507P83+zWFF2d7tyLMlVsZIwpnY4yIRsA6fJbbhxoMl13GcO9LiAXydLElABp812uEDBL9+X/OFMiQx8v/bSgy1P/dDpISkhpHI1UzpQa7CsgCaawy0aCAi7E11CXCIYoZw4rdcpHnEQ4o7mKKi8YkFOZ5ImrNST1/9ANYOMIkVqTkF9WwhnB+Qy3lEdvnaS8NRiNE6+vc5XzKtX/TKaMnXfLBIw0imJW6bWpfbWOLw/mLa2Nzpa5Usfn6V9/BumN3+PobboSNYujTvr4mbmgsWSm9eC7rWoNGDZrc89hgzMoWuovR0MKgEy1dW2w1sg67ef9mVKr0PHxR13+NztrerUiZFZ+Ai3cL+XHfxF8xm00sYOVvWUeaOtFqbGB+CMECgJiEV4FZLuiXKM5a8FWAXwAWYXwcTFufzcSAxuzqyyphJEXWnoexHkRttjLLW+tWZ7C9hhn3K7IHWmFWWg48Ouqo3s/fRWnOZ1NgejFl5oF16vlVfC2BsOAMbhRjd7QOoNl0DVYfki2WBpkpag2SbQejx7djz1ONx387+HF64e7yaPZ6ORYxkH35HbFbPfside5AmuPFDkz/9xQGptK0HdFmbGY9NVMQjNofZyOj2WtZl2hTK3cvhZFXwj+M314GM6gUVCWPqIoAYCCcH6hFwGHeCBZQ8gM1sihKHq95JlMulaPxLVN8rBSngcmOMH+DAISj6Tk8v98nX3+FovGoTImvs6FyHj8BHIEw806TZiNU5uXWIT5iDhdUFDrpl1PmUzUCr1OzelH3s3xPymS7z9NoKAksLralPR8aAJAVk1Yvh6ICx/RcuEAxfrn4CKn8Aj2fpRTsEITHnZykYX1KkoaWIUkaNiWSNKATSFkFgGsZL3r5LPJdIgYXUx5569zLqMT8UtSrkuYyvZRCUTEoYjb8Q0AV68FKhFsXjFkmaZ8e7BSx1Oa4+uk6WRTCyNuey//+aqYIMUTbMp+1IVNUP54sydXF6f1kvAvqFZOBWHUJYuXyHQRidehvdnq12swffzrTJGoYL3fJOjLT4N90HKQ4GTHvCSxd8ebN1Rb4Hx4uRydIZAzwgCWyewffkB+vUaHTNcxsLlP/5BGHn4NoKk/GCjwVc3o6ErSRhGM8y+FYm8la9ogiOG5tA37jdyRaj+fugOO7AlPyxtvG+JJmfDwWktvzOm5OeXG6LJ+RR+UzXkWzyyT++xvjBSgok36ieodIR40vTJfZ9QnlEoZmondUGIOshJNRk8bbgEZ3iohKPEdyjHXlzx8/rUfW0Q0kiwv5+4AwMvQxNUCvRQTo7VtxiVTs2RSj58SCmyRW//nV87o4n9FqodzuvQYt8Mot+IyZgkNckX5dmeBr3gDskHJFWRVWiq7OBvZMo0uAV6gCoyaggUzv/Fx1NK/6SKcq77eQOnmyuDeaf/N3F+hyDpkiNlGFpJERkhR0pRzwwxmUtogcfVyNsPk684lzZjMKxqFe7MP5kf7L6q9AhM1vxhflJce63Sbi41lHMqsdqYdpjonUY81KbSPy7bH5XvqrlrIiF6V2RQpBfXc1V0qBDiCf7RR/EUFMvHmr1QQv4kzUHCnKeY/oWE1yJKpaVItW
*/