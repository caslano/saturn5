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
R0vhlIvp43D+fnw6p4/96bQ/mp/R+B31R2etvw/D0VtwQyGqJXm9stIBhSVVrUols63g31Hp8/fE/VxI4TYLlC83tqLn1PuRToQFpw+e9qhXqiUfohfJiztPJ0LXouxFyew9jfong+ihoz3q7gQtS5NeKn3R0NdboV0ubbCenY3Gk9lwFiWH9IPSaVlnkl6zu4ZsxZsocSvsDql3dDo9Tg32H0Tb4S160qOwWIAWiNPbfQWEIgtx3g5mR9PhZD4cj6KhvjKXslFDXuuUlUAiR/fpPB/eOlda+Z3nu+f5JBBNlCUTI9o646QHx9tTKY64IKFKZC091wpmXSkCydr0Iczogb7hC2BcQkNPVe08LWXwKtmRL8IZJyoJoId3cg0QXaT0qvYseD72pVTYHaaDhxKYW9vpdPVsjrZPjT+pvbI8V/6uJYAB8J3GVkJrdJQTblw7qFBqSEyjDszlnCDSHDMFQekdVrTRezf2S4mhpYyNofrbCld16dU2JgDm2ZIK9o0Cb0hUptZhvDXlh7C/khJGJqhROw7Kzfx8MVH/PExUpTHNw7C4aVtlLHMHAJBbYHQcjqLtkbxCzlKnprbi4s6QSahTTqCD59II72XVjEcr9zAhb5obpQbVbGgJ6M3gN2Vp1gF1CwRjxRe1
*/