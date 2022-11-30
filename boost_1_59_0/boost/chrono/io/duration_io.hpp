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
#include <boost/core/no_exceptions_support.hpp>
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