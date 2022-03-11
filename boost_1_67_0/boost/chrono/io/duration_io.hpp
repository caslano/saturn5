//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_IO_HPP
#define BOOST_CHRONO_IO_DURATION_IO_HPP

#include <boost/chrono/duration.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <boost/chrono/io/duration_put.hpp>
#include <boost/chrono/io/duration_get.hpp>
#include <boost/chrono/io/utility/manip_base.hpp>
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <locale>
#include <iosfwd>
#include <sstream>

namespace boost
{
  namespace chrono
  {

    /**
     * duration parameterized manipulator.
     */

    class duration_fmt: public manip<duration_fmt>
    {
      duration_style style_;
    public:

      /**
       * explicit manipulator constructor from a @c duration_style
       */
      explicit duration_fmt(duration_style style)BOOST_NOEXCEPT
      : style_(style)
      {}

      /**
       * Change the duration_style ios state;
       */
      void operator()(std::ios_base &ios) const

      {
        set_duration_style(ios, style_);
      }
    };

    /**
     * duration_style i/o saver.
     *
     * See Boost.IO i/o state savers for a motivating compression.
     */
    struct duration_style_io_saver
    {

      //! the type of the state to restore
      typedef std::ios_base state_type;
      //! the type of aspect to save
      typedef duration_style aspect_type;

      /**
       * Explicit construction from an i/o stream.
       *
       * Store a reference to the i/o stream and the value of the associated @c duration_style.
       */
      explicit duration_style_io_saver(state_type &s) :
        s_save_(s), a_save_(get_duration_style(s))
      {
      }

      /**
       * Construction from an i/o stream and a @c duration_style to restore.
       *
       * Stores a reference to the i/o stream and the value @c new_value @c duration_style to set.
       */
      duration_style_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(get_duration_style(s))
      {
        set_duration_style(s, new_value);
      }

      /**
       * Destructor.
       *
       * Restores the i/o stream with the duration_style to be restored.
       */
      ~duration_style_io_saver()
      {
        this->restore();
      }

      /**
       * Restores the i/o stream with the duration_style to be restored.
       */
      void restore()
      {
        set_duration_style(s_save_, a_save_);
      }

    private:
      duration_style_io_saver& operator=(duration_style_io_saver const& rhs) ;

      state_type& s_save_;
      aspect_type a_save_;
    };

    template <class Rep>
    struct duration_put_enabled
      : integral_constant<bool,
          is_integral<Rep>::value || is_floating_point<Rep>::value
        >
     {};


    /**
     * duration stream inserter
     * @param os the output stream
     * @param d to value to insert
     * @return @c os
     */

    template <class CharT, class Traits, class Rep, class Period>
    typename boost::enable_if_c< ! duration_put_enabled<Rep>::value, std::basic_ostream<CharT, Traits>& >::type
    operator<<(std::basic_ostream<CharT, Traits>& os, const duration<Rep, Period>& d)
    {
      std::basic_ostringstream<CharT, Traits> ostr;
      ostr << d.count();
      duration<int, Period> dd(0);
      bool failed = false;
      BOOST_TRY
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        BOOST_TRY
        {
          typename std::basic_ostream<CharT, Traits>::sentry opfx(os);
          if (bool(opfx))
          {
            if (!std::has_facet<duration_put<CharT> >(os.getloc()))
            {
              if (duration_put<CharT> ().put(os, os, os.fill(), dd, ostr.str().c_str()) .failed())
              {
                err = std::ios_base::badbit;
              }
            }
            else if (std::use_facet<duration_put<CharT> >(os.getloc()) .put(os, os, os.fill(), dd, ostr.str().c_str()) .failed())
            {
              err = std::ios_base::badbit;
            }
            os.width(0);
          }
        }
        BOOST_CATCH(...)
        {
          bool flag = false;
          BOOST_TRY
          {
            os.setstate(std::ios_base::failbit);
          }
          BOOST_CATCH (std::ios_base::failure )
          {
            flag = true;
          }
          BOOST_CATCH_END
          if (flag) throw;
        }
        BOOST_CATCH_END
        if (err) os.setstate(err);
        return os;
      }
      BOOST_CATCH(...)
      {
        failed = true;
      }
      BOOST_CATCH_END
      if (failed) os.setstate(std::ios_base::failbit | std::ios_base::badbit);
      return os;

    }

    template <class CharT, class Traits, class Rep, class Period>
    typename boost::enable_if_c< duration_put_enabled<Rep>::value, std::basic_ostream<CharT, Traits>& >::type
    operator<<(std::basic_ostream<CharT, Traits>& os, const duration<Rep, Period>& d)
    {
      bool failed = false;
      BOOST_TRY
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        BOOST_TRY
        {
          typename std::basic_ostream<CharT, Traits>::sentry opfx(os);
          if (bool(opfx))
          {
            if (!std::has_facet<duration_put<CharT> >(os.getloc()))
            {
              if (duration_put<CharT> ().put(os, os, os.fill(), d) .failed())
              {
                err = std::ios_base::badbit;
              }
            }
            else if (std::use_facet<duration_put<CharT> >(os.getloc()) .put(os, os, os.fill(), d) .failed())
            {
              err = std::ios_base::badbit;
            }
            os.width(0);
          }
        }
        BOOST_CATCH(...)
        {
          bool flag = false;
          BOOST_TRY
          {
            os.setstate(std::ios_base::failbit);
          }
          BOOST_CATCH (std::ios_base::failure )
          {
            flag = true;
          }
          BOOST_CATCH_END
          if (flag) throw;
        }
        BOOST_CATCH_END
        if (err) os.setstate(err);
        return os;
      }
      BOOST_CATCH(...)
      {
        failed = true;
      }
      BOOST_CATCH_END
      if (failed) os.setstate(std::ios_base::failbit | std::ios_base::badbit);
      return os;
    }

    /**
     *
     * @param is the input stream
     * @param d the duration
     * @return @c is
     */
    template <class CharT, class Traits, class Rep, class Period>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, duration<Rep, Period>& d)
    {
      std::ios_base::iostate err = std::ios_base::goodbit;

      BOOST_TRY
      {
        typename std::basic_istream<CharT, Traits>::sentry ipfx(is);
        if (bool(ipfx))
        {
          if (!std::has_facet<duration_get<CharT> >(is.getloc()))
          {
            duration_get<CharT> ().get(is, std::istreambuf_iterator<CharT, Traits>(), is, err, d);
          }
          else
          {
            std::use_facet<duration_get<CharT> >(is.getloc()) .get(is, std::istreambuf_iterator<CharT, Traits>(), is,
                err, d);
          }
        }
      }
      BOOST_CATCH (...)
      {
        bool flag = false;
        BOOST_TRY
        {
          is.setstate(std::ios_base::failbit);
        }
        BOOST_CATCH (std::ios_base::failure )
        {
          flag = true;
        }
        BOOST_CATCH_END
        if (flag) { BOOST_RETHROW }
      }
      BOOST_CATCH_END
      if (err) is.setstate(err);
      return is;
    }

  } // chrono

}

#endif  // header

/* duration_io.hpp
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
*/