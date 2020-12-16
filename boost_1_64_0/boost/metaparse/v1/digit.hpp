#ifndef BOOST_METAPARSE_V1_DIGIT_HPP
#define BOOST_METAPARSE_V1_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

#include <boost/metaparse/v1/util/is_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<
          change_error_message<one_char, error::digit_expected>,
          util::is_digit<>,
          error::digit_expected
        >
        digit;
    }
  }
}

#endif


/* digit.hpp
P+CMX8vrv9e2cCGWGi+Rny2NP1Bpt5f9rzPxGfxLF9db2/7XWfh04S3b2PbRbPwu4fteZdtHc/Cpwm/Gi/mFPtHP72lcO7/4p/SvOv2Psn+wL74VrzQutr8If8Jx+ftegf/dcfn7Xo/Pclyuz5f5PBw0OOWT7fOH8Zdx2f9i2ueL8VXCs7iJ7/wHvkJ4UG3jt57An3Zd5k/6iufH6Z+W7ed2eD7E8ayTH8+2n2P4G8IH4ub+6IBvFj4bD5nvB77Rcbk+ZuabcPC5En84D//Ucdn/+SS+wXG5fvhSPOe4XD/8KfxV12X8W4MnPh9X5/96PNiu7z+Kq/H5Ho/j6vfPc/xaz/7rPJ7EtfWXM/h12u+PX+O6bH9/q+ffqcW7lqhf71fwUfhu+EDH98rb/AWX442ED8FN//U4fEewsz+Em/sr9x3x4aHy57ce/4Prsv8EbxpSxp++DwdvOfUvmf/jOvyfhfIZ//VsZ37sD/+PX5Pfz4MK/8X9+NiA9oHj6x91nj/8QOHNsu76qv8f/5Tf/7i5P/B98RHWad/Y/a/Ec6GdfRlu9r8dzwg/6j17NQb/RH4I4Rm8OP/iZxE/K/Nv4bcp/T8N+OnK/IPt+GmOy/bLt/gp2vz4X8hPoOVvxZcGMv+wM36Fz1DyD7+BDxB++btO++VX+m9D5fufR+PtSoz/mO/bJXjrEuM/Tcz3F99D+DLcfD/G4RFl/Ce/g/glZ/xd5nf7DT8STzrecam9/r/jhwvf8K69Pmf+9v/2t+v7b7VHOwtfKPx2vFi+IKLn18PV70NI9yiu5ufC1faRZ/8Jj9d6vA5PFKxUfuYs/pjz/pHP3xI867h8/tIVkeBm5fmbik9Snr9p+ETl+Us0ioj89OL9gPd2XZYP76dsPxVPaOu34O21/HKVutfizzv973J8ZxD+rONyfOd0fKnr8vo0juj56/B9tPzfeHvt+nm2n+rZvt6z/QrP9g24kv+PCxlRxx9CuDb+UOfZfrhn+3r8SO388MO19a93jejxW7i6vgXeVvEkPt55vuT435X4lY7L+SNX4WMcl/NHrsYvV/JHRZtExPrOon2OX+K4bF90wIc6LtsXnfFThHdy4l+OwhPCJ+PF9g/+ldY/hn+hlO9R/C2lfE/gGx2X7Z9/4hu09Sd2iwQTQuXzJ76NX4aXy5+Yx0cKvwg37cdt+Ai8XP7E9/Hz8HL5E7NVkeA2pf/xRXycUn97Cb9cGb+uC0eC1tr4icczHq/3eB7vrn3fI/r2CVwdn8THlXg+dyv4EHyo8v08Ez9NG5/G99byz+yuly+Oa9vXebZPejzl8bTHMx7Perze4zmP5z3eoDsdabpHcXX9WFxdP9azfdKzfdqzfdazfc6zfYNn+2jUc/64ev64ev64ev64ev64ev64ev64ev7NPOePq+ePq+fv8bRn/1lcez/kcXX8vbnuMY8nPF7n8ZTHMx6v93hedwZ4dI/h2vh/wuN1Hk95POPxeo/ndacjQ/eYxxMer/N4Cj9WKz9+khafhA/Q4pP2jAQ9tfFFvFapf07FT1bGZ4NWkeBU5/mV/VNV+PGBzXcqx2eS+DPK+mRj8GWOy/rHWPxxrf7WWu+fSOIrQvZvOX44Hn8Mb2Kd8RF7/D/jWcfl+kGP4BOED8aL+W33igRNtfnlHs/hd2n5q/Cpyu+Xbkv7bxe7fzm/ZiYe4HHrzD+y61fNwn9rvLPvwMNm/BD/VfjJNFiqzPokeIPwJbj5K96R+mVl+fmFx+PV/Eud4wPfsP0XNXgr4VPwYnwwnmm0s7+Hm99nBT5HeP83nfbbAbRfSpTvYJPfAz+Efxnn+Fubibsw7Xe8o/C2W7g+hb9W4DHhl+I=
*/