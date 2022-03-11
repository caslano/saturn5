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