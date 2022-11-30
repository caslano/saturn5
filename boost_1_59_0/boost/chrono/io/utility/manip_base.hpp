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
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
*/