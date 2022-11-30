//  boost progress.hpp header file  ------------------------------------------//

//  Copyright Beman Dawes 1994-99.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/timer for documentation.

//  Revision History
//   1 Dec 01  Add leading progress display strings (suggested by Toon Knapen)
//  20 May 01  Introduce several static_casts<> to eliminate warning messages
//             (Fixed by Beman, reported by Herve Bronnimann)
//  12 Jan 01  Change to inline implementation to allow use without library
//             builds. See docs for more rationale. (Beman Dawes) 
//  22 Jul 99  Name changed to .hpp
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_PROGRESS_HPP
#define BOOST_PROGRESS_HPP

#include <boost/config/header_deprecated.hpp>
BOOST_HEADER_DEPRECATED( "the facilities in <boost/timer/timer.hpp> or <boost/timer/progress_display.hpp>" )

#include <boost/timer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>  // for uintmax_t
#include <iostream>           // for ostream, cout, etc
#include <string>             // for string

namespace boost {

//  progress_timer  ----------------------------------------------------------//

//  A progress_timer behaves like a timer except that the destructor displays
//  an elapsed time message at an appropriate place in an appropriate form.

class progress_timer : public timer, private noncopyable
{
  
 public:
  explicit progress_timer( std::ostream & os = std::cout )
     // os is hint; implementation may ignore, particularly in embedded systems
     : timer(), noncopyable(), m_os(os) {}
  ~progress_timer()
  {
  //  A) Throwing an exception from a destructor is a Bad Thing.
  //  B) The progress_timer destructor does output which may throw.
  //  C) A progress_timer is usually not critical to the application.
  //  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
    try
    {
      // use istream instead of ios_base to workaround GNU problem (Greg Chicares)
      std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
                                                   std::istream::floatfield );
      std::streamsize old_prec = m_os.precision( 2 );
      m_os << elapsed() << " s\n" // "s" is System International d'Unites std
                        << std::endl;
      m_os.flags( old_flags );
      m_os.precision( old_prec );
    }

    catch (...) {} // eat any exceptions
  } // ~progress_timer

 private:
  std::ostream & m_os;
};


//  progress_display  --------------------------------------------------------//

//  progress_display displays an appropriate indication of 
//  progress at an appropriate place in an appropriate form.

// NOTE: (Jan 12, 2001) Tried to change unsigned long to boost::uintmax_t, but
// found some compilers couldn't handle the required conversion to double.
// Reverted to unsigned long until the compilers catch up. 

class progress_display : private noncopyable
{
 public:
  explicit progress_display( unsigned long expected_count_,
                             std::ostream & os = std::cout,
                             const std::string & s1 = "\n", //leading strings
                             const std::string & s2 = "",
                             const std::string & s3 = "" )
   // os is hint; implementation may ignore, particularly in embedded systems
   : noncopyable(), m_os(os), m_s1(s1), m_s2(s2), m_s3(s3) { restart(expected_count_); }

  void           restart( unsigned long expected_count_ )
  //  Effects: display appropriate scale
  //  Postconditions: count()==0, expected_count()==expected_count_
  {
    _count = _next_tic_count = _tic = 0;
    _expected_count = expected_count_;

    m_os << m_s1 << "0%   10   20   30   40   50   60   70   80   90   100%\n"
         << m_s2 << "|----|----|----|----|----|----|----|----|----|----|"
         << std::endl  // endl implies flush, which ensures display
         << m_s3;
    if ( !_expected_count ) _expected_count = 1;  // prevent divide by zero
  } // restart

  unsigned long  operator+=( unsigned long increment )
  //  Effects: Display appropriate progress tic if needed.
  //  Postconditions: count()== original count() + increment
  //  Returns: count().
  {
    if ( (_count += increment) >= _next_tic_count ) { display_tic(); }
    return _count;
  }

  unsigned long  operator++()           { return operator+=( 1 ); }
  unsigned long  count() const          { return _count; }
  unsigned long  expected_count() const { return _expected_count; }

  private:
  std::ostream &     m_os;  // may not be present in all imps
  const std::string  m_s1;  // string is more general, safer than 
  const std::string  m_s2;  //  const char *, and efficiency or size are
  const std::string  m_s3;  //  not issues

  unsigned long _count, _expected_count, _next_tic_count;
  unsigned int  _tic;
  void display_tic()
  {
    // use of floating point ensures that both large and small counts
    // work correctly.  static_cast<>() is also used several places
    // to suppress spurious compiler warnings. 
    unsigned int tics_needed = static_cast<unsigned int>((static_cast<double>(_count)
        / static_cast<double>(_expected_count)) * 50.0);
    do { m_os << '*' << std::flush; } while ( ++_tic < tics_needed );
    _next_tic_count = 
      static_cast<unsigned long>((_tic/50.0) * static_cast<double>(_expected_count));
    if ( _count == _expected_count ) {
      if ( _tic < 51 ) m_os << '*';
      m_os << std::endl;
      }
  } // display_tic
};

} // namespace boost

#endif  // BOOST_PROGRESS_HPP

/* progress.hpp
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
*/