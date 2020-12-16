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
8+YVFqEhstSRaK0tyLqk0HNKlrH1GON1e46lW9bVOEJdwa0wpNzPy+pXrxtx1xfdiNSR1fWr3tsb6lepE+K3or63Pkm+67nkyDe4MZ2MY7yuZ748i7eNY9vzyz4nmHlF9xRdj5lPdLfoIphH9n7yI9QzzGcbZAbsirTu7Oeru7oRwi9IO0T/Q3X+B2iP6Geg+MF9WV27RL9JAevxVH28W7XtRff+Mm7Oelh9e6HbK7b3s2oYw0gP0G7k+rUbbhW4jpQrax0JXhfsc8Z1mqX8erJfvnsUx9FRjp3I7uY6JXLtyyCscxfD2aJ/K+FuOTqf6He2Ggf7NNgfE3uEKw+t2QGVjH6BFupPRivsvNEcGrxE7G3ZTt3ujFJDQ6LU6pBQtQsmOjRU9YNZAtNQ4jHUJ0PMeFZLHlfY0sAk+NotpmGq3sfjQbEnuOJFywI3S3xS5lInCjLKLWWequOZqPft+J3Y27raGSHwA7dA8djqDvcDGeDbD2Qq4/XW723euiRhdbnAbWzjcwzpz6N/tB941FR67SidfFeLgPU+mrqQVeJvmCuF6zpPsqaX8Sf5xf+CPX7/e0av63yT+Onr6mx4rmtCgLiT/eLeGSBuvXcBIk/kHib3iZ9EV7QRp25y9lO3hrZQJ0NjedxQj0l+PhXaUF3ieNzRw/EjdIxNQplWiS8zV1meQy9IfCEul+Gkm8F6+ZSrEdRAvrYf4z8LM/LLsn06yK8H+z/jCvKs40zJAz3jUBO5vsNGibeLaxFK7kOVijW7u6mdUGkewyv1AEcMUpyg7nP2VuNDeqg7Uef/DtM+NEqNDG2qfhuK1aVdLkljHq7zDsnPPebqPHATTZVOdxNb/smYsNbrXS9+hrhGGAb3n/Crp548Kis2h9l8z05LfLgXLOO+b8s1dlUTuc7F/RJ/M9dc1Qr39GjsMx+DNTmbqYPYdaa9o4+a54jGPd1J9Qzpr1aExKkXYcJC41Q/XOeC0Hj1FUy0xOW7xnjVQ65xurneocT/jCuW9bvUk15PJcEvkWuC3y7+OuK+jsPyAUvU+87rlcPVhMd1PcFZF0k9+S6ksa4nTSROT2EnsqwbDZJ2w4FeHFVfOVVjcIL6wIhn27Zejl+gPMfRrwI/XdHWNzDXJIjxmKM0X3kN3Y/BBF+Dy77PTfuhtn1uUHZ2+w7azbXIbxvi3UNm0EBFt/U+N70nTbp2S9Z71wzyuem9cI4O1m5635ud2m3gIK/bWp+bPscqn5veR2eazy3J6zZFuw3Q8TX2uen4ygd53fprf6U+N30dXydrN723zis+N30do7RbP70vzwsD9X5AOv/u97np6+io3frotOwaoN30eU/2t+wRxOduhdYB83lJ903anc503wriWQJ3PpPovo3u/s/1SrDUZXuui/sLQd4Zdvq/M9jeE9kucJy660Dqm5p47Du03T6mvzcq8Jh+yvDaj+mL32rG9EcNP70x/Z5M6zqO6RMqCmYgEuz2pDVjbkkaGgZPOkcqpJPthJmOZ5TXXxTtCDGczzjxT01lWb7kt7+f4GlXtrSPlLKQ89ryeZM0XLL2NeKCP7AX0r7ak/asogx3cRq2pcjMrfY9jf576v2LnhR7S6Oa9yqG6abnNjwu9g6G793HUnf4nrBN/CQafKdiHJ2DvndN1X46cJ86rIMr9t7Ul8t5rO9H9G8E+M4rLXDz+8X7PL9zhKeORYsd/4n9YeTx/fzOE72xmDQyshb7QnB9roD3eXKQ+zxF38/MN7qP1+6WvLF9r2Xa6vNzrZT8tiBMN7KvqRlLkTqRU1Ca467hvZ1+p+r9A68X+wWuC4361b1rM1yahDPr5O1in+yajNIKVi9Sdbh8/W4=
*/