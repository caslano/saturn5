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
7Om0ZidqvvnK2j31dX07jvnTyvAQXUIuRHNy8ciMgkOmecDyP7eVzT5uvj1F2E/+v00oXOEoAzeOeCcZvzgCRAKoae1UZgZ20STweHmaMmWtPs/BiGEPaKUns/7NkpqhDOsF0G93izTPS0FZwRqnIdDspAelRIR2n+95gHVuF3NJAstWJNQMObDhOPUTLqFYB6gbEPAZPaRn1cxJ1kMqh6CAJ33WTPJBIrKG5wKD6U1x8Es7OsDYZoX6CZCbNCV1CdKgucyx3v9q1A0uRfHyRTK9vXlrMJ3B+2+DSDecbd6XJyUBqT7921CIj5V/hPXhn4G+0L1EBEP9RbjU/EdcMI17i5Jd/liO2F/8ZDrnSyaD/HcP+fjimQJl56ySBsTLFAz0jjECqg0cisxcXYG1UQ2Hc8gU5t3uVrlQYvJQeSGiMB3rWFwSx4ujHyPTJVj90sEWtcscpdeJxy80zl+JViBRv9G2t8f7qsvojRKLvLsM2uyXvm/NlBOXtHyqBfKFF833eW6IxUsTqRZHSEJVds5Hp/5fogDIUnp2odfANrb6XZ+/sn4XJK19zw==
*/