// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template<class ChDest, class ChSrc>
    std::basic_string<ChDest> convert_chtype(const ChSrc *text)
    {
        std::basic_string<ChDest> result;
        while (*text)
        {
            result += ChDest(*text);
            ++text;
        }
        return result;
    }

} } }

#endif

/* info_parser_utils.hpp
/K7rN1ILa030E8buufWBun7fNq+PVe3A617m9P3pz9X0HOYk/SvJZ2Gt/qvXLrmm2aV0Xbm7jzeMJ6D7F2O2T5YEdWLW5e6unCmRZvUmcrqhtveo82+q1bfl9CXv5bvqcBlz+PR9suPO3tW53Wu5O7kOd1Ybx1Y8Dt+R0+eoa5eNe3R795R7dU8OJ6Tn8oioyV3t51yDOznG8aHbq1dX/u7Z1YubB3/St327zDi4hznFGltMyFN2npAcGneSm3ZsV22tAYefNO9PX6eWavMP/RLTvoa4IqYpctk/Ozft87sn5bsRxb124L44On1No659wpCYumaoMLmsSJzxjc2H07WePY6swwkirKj3YOF++Yx5qAZV1s66h09fU8Q9ZnLo02D5N/Pvnp7jsvcyFrYpeZzmGrewBnHI8uZqeD9rB+v3N3aW2q1byI/ppcRLy+EyaiUe0aH+c3NMPwFRkmTZtC3MHivy3GBNnzE2aWyrA7u3NMci8hHXKd1HTtbl1CW1idJlZ64fIveW09Udc01jUcfZz5x75npzxc+Y6+ZtT3vBzm9dD3ZO72v3RMi2M1P3Mq3fyPH31laxJpbsf0hcO8uQsMfzqRpS/K26c/Q784kdztBj8lvri30OGP/avDg9Nw3tLHskPQ793hjsm9cum5ddhn9w/B9dS3H3T4gZmp4LkSP9J32xob3+BzmK2+6roG/tth6dFeesf8Mc7+lPnPxA399Xc3EsFs6vnldW1/vzHmMiwpmq87zbOWpq9TF5iidvsa3kmPeL73Svv8V4PmTfdzmvfS7ruPmbtN9mrCV5vc9xp/H9cvN8xPPRD6if9sy+qbeqTdX+b1brsjzfbb+P6++t6l6Vi+Nazl+u6fOD6sKwrg5UaX/YsfIYvEsOH1ETCh91D9CmLr+thnG/w5iZfkBd7D/U1xX1ufoWx3u+rR1+q8cfNx6Px86Tl0tfnhtvVYOyehGSz/y9+nif83DFuvgufZA7jaf92z5+u+NLrkXVOE7HadyRtzjH23D+/YbHHzN2Zm815rcb53vlUtGH9iar8i9WbDf+4Vs81h6pQ3Ba7w/oo2QuEK2r8Yd5v/4+6tysNfT7VucTm/qcvlskr914l361tysiLfWoyzv8Xo/Jf8jjtxvHm42/auzvta92itzbnecdtn3Yc85xXJY7VXU6+3H5fkye5N4pB449f+DcnQrqtSunVkMfzJ1jhaT+gpr4QWsnGx92L31AnmScc/Ux1vinu6+p0WHrmdYPUmSpvsF9zFZRn3S57BvlmjB2LvsQ9yUZqgxZfaj9SVGiT+hh+idJgQ4LrpE0h8jSYMzZ5/qe1MPVnzQVBoQf4fqxT5kRa4/UFwcUaBPdc23FK+573eCIKtd5qvuK3Zspizi9uc/LxOukPU904XtY4oCVp8mDJFXmH/W9B7HzSt+XeLrnaRA8Q/5UmbOesabRIXShwPfWnJsqU44eei6fQfhQ75G+B/Ms26gyZ3L6cxLPVkuahI/kStwfS8+JTSo5Px/wHLmRpMmUM88Vd/18xH8Yuxe4yPY5AOAHgxBCCCGEELrsslh2qun9GtdiPdtsuRttpQe7hMUihBAWIYQQQgghhBBCCGERQggh5PGdOvOo9drP/d7fzPz/5/86//M/Z+ZMJQ5yiZznGONZfSXmcTejLLDF0Qv2KXNEnqvffh68XhxhmSI/8531PG1gjEV26LuLtOcrj3l2WL/KPb/T7tMPKpNlCl8gL5OskfNCdTLIDGsE/u5P3ovsU2bIHpKHQY72+TxVHPyIdrzY/OEkQ8yQk/jZRTH+EmPGPJeuMBYv1b6cIDjOCDsPldfv965+mPEQB8QFNlm/hc+TH64=
*/