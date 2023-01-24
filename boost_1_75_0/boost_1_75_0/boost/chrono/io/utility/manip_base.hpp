//  boost/chrono/utility/manip_base.hpp  ------------------------------------------------------------//

//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_UTILITY_MANIP_BASE_PTR_HPP
#define BOOST_CHRONO_UTILITY_MANIP_BASE_PTR_HPP

#include <ios>

/**
 *

 */

namespace boost
{
  namespace chrono
  {

    /**
     * manip is a manipulator mixin class following the CRTP.
     * @tparam Final the derived from manip and final type
     *
     * @Example
     * @code

    class mendl: public manip<mendl>
    {
    public:
      explicit mendl(size_t how_many) :
        count(how_many) {}
      template <typename out_stream>
      void operator()(out_stream &out) const
      {
        for (size_t line = 0; line < count; ++line)
        {
          out.put(out.widen('\n'));
        }
        out.flush();
      }
    private:
      size_t count;
    };

     * @codeend
     */
    template <typename Final>
    class manip
    {
    public:
      /**
       *
       * @param ios the io stream or ios_base.
       * @Effects calls to the manipulator final functor.
       */
      //template <typename out_stream>
      void operator()(std::ios_base &ios) const
      {
        (*static_cast<const Final *> (this))(ios);
      }
    };

    /**
     * @c manip stream inserter
     * @param out the io stream or ios_base.
     * @param op the manipulator instance.
     * @Effects if @c out is good calls to the manipulator functor @op.
     * @return @c out
     */
    template <typename out_stream, typename manip_type>
    out_stream &operator<<(out_stream &out, const manip<manip_type> &op)
    {
      if (out.good())
        op(out);
      return out;
    }

    /**
     * @c manip stream extractor
     * @param in the io stream or ios_base.
     * @param op  the manipulator instance.
     * @Effects if @c in is good calls to the manipulator functor @op.
     * @return @c in
     */
    template <typename in_stream, typename manip_type>
    in_stream &operator>>(in_stream &in, const manip<manip_type> &op)
    {
      if (in.good())
        op(in);
      return in;
    }

  } // namespace chrono
} // namespace boost

#endif // header

/* manip_base.hpp
NNssBQ8bw6sMqfz5VPeAqt6uf8c4e3GurYUY3+TiUSV+Cddud0qXMmHE5BrCF4QkxjuiYhxGfnvV/BTPnYUL/wWS62wkDLBchuSq313/BjlDBOGfGrHqzMJ/m0HqmPw/WxAKMZBQ7F1OK7dVCC/QAd8zcL+zsfBFNcm5Ez/Oag0fDzubTB9YTuq4CikfFzzBvoZNTxxYTT7/1uiyWPUy2Ncw7Wf5BKr9zACUzgQVaJYUERp9jJF5fQLm9biuznl9Ysb/L/N6bmLd8/p3jXpec/8OdF7vOVPbvL5/xu+8noXP6nldML7eeZ0J87pI1Nc1r20erW9ek0AiqVTmFdzn1DOvMTaXOMbZp7aJ5brsE16/VzWxIfz2yvn0umahbaGIkxvG8XuETb0o3J4gFQY5G8Gnub0JgFWRXDDJlmxw6YMTbdtIZxenuyXMLJm5YmdTKHP6TzJ5efBt45M4r6WWvGKnBSYc6+RuJnW+ZsvHpUgcuMvZfPrAo047JL1Okipn40Xov6TUFuTf3QRuSPLPkHwPSS5wsgVrzfH7SfpZsuQee6GQ3Y1kiBfh7PIwt/UPssk/JVUTynI6Dtvyn5A+ysWbYvG3o0nxy9eg+aelLH2xeZq+Ddr/kaRjSrt82IamD9xKJgBSZ9xKUjejBdk2MuL849hHMj2qFpr0JHlWkDwq2IoaWy9sPQSwBfEuyPvD8N6evj8C7+H0fRa8
*/