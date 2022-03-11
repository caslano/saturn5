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