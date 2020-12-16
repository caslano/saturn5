///////////////////////////////////////////////////////////////////////////////
// rolling_count.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // rolling_count_impl
    //    returns the count of elements in the rolling window
    template<typename Sample>
    struct rolling_count_impl
      : accumulator_base
    {
        typedef std::size_t result_type;

        rolling_count_impl(dont_care)
        {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return static_cast<std::size_t>(rolling_window_plus1(args).size()) - is_rolling_window_plus1_full(args);
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_count
//
namespace tag
{
    struct rolling_count
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_count_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_count
//
namespace extract
{
    extractor<tag::rolling_count> const rolling_count = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_count)
}

using extract::rolling_count;

}} // namespace boost::accumulators

#endif

/* rolling_count.hpp
Id2Y9b7CNzcDSYruZjM6EYTxNCRjc9wla3kQwki8HY7PGeYq6KbtX6E07I38oNq1FN2haBrE7trvRml3uyOMvPfWEfUMe70Qu6O/w17PDd1ebCcrLg9UtivbKx0v86UrAVfHsE+tZrlMrTSrg+hQKlJseyb0V7s9OYf9laNXaSJbQxCGsr6s2EpWTW2aVM9q/1jKZ3jXZJIsYxB7Lwb/dcXRaWAUrSEZYIAUm+rOvSM+xJOSSe6f5aE84WMusbe09OJQjAlvFx1UKN37qRp9LZ+Y+Sm2QMJ+sbjUTCrFI3Ilh+cLVr9uAqxGmVht7ayGwdwKn9yToUxmfItiT1tRFNS/r/iLlpXu1cHiLmBWq6mhkPSljymBAMJzI/V9ABAEnIL909RRP+Nci2ydfZ6u1IVOFjZ8AfWgjvDRoWrcFdwBkoKxuj+tVeRIGoes8Nwz8Z46Bl2VfgTCtXgJ/ryxpt7Jzc3NUhtU/yHiNR1zM6Zt+FM92WbDIcRTB+AtkWTQcgV2/VuRISUrtJ8NOWdL9V+qiGtYE55WON7XXafr712x/qd6ElPtQ6B2YQzlXE1zk49/vbszf+qkWXETqrygP6H00nQqlSGNhiKewLmCNThL3W6oic+OP85fo1vczd/uFs7SaLujFs/HgTwfoV7O7yR/6kG7gyKesSSQeX2UZZpmlcfxb+JB+/w+AetBv0EGeWXZXCRIvgbd+sk+d6GIs0BouTMxv0ZjFAYMq0sIaxsH5v9RB+bllyP68mHanGHMd3PB6IGD5ySxCeEoLX+gMHtOGTWENxB3g/oCV4wfhnL9r8bawas7nGUFIiv3yAvweMkqoAK/O1sBZPoLZaotgM2hV75DDahdGurv24vBw9GYnlaot1DiS1f9w5aotefeP784kAdJjWqFTm5eGnK7th41BsQXLH+O5MdqVVdEIjn8FfUukMAFt16Dgmf3H1veaclFUiPuGYrFt4UPn8SD+Vmfe8+Q0C6drKTt8cW88ERjVuevkZE/2qZduGanGE6hcjoVLjMMvAhj6t6I/FO2hohyh1rfjdmS1VVBRp48o07XDkPSvGdUvWYyTotCIa9webchTWVj1hWyDzeSuw6PICFFTJwBizt/uC3de7sDiKjRSGZ7z8WR5CwmAh5kS16yMY5OxEjSRZIURTtolhDcJ+klOj1M0scBn98iSn0T6zei+LjYUUbunUhi6cRqtRP955tDScSorEEi8hRzjRtUoc4wjDMsR8pSpJT4DPVskqvdZWnlYZY8rkJFTyIfxGJ+/8twe13T7Vvu6pYR4suJdOcer5nzPQfc9rSjZDuam1xnyV8jEhZouqXV8eVMdueeCM85SGqN8iR9vr7OWWncVKrNWQLpYgTYyYk8VK9DvWgZSicK4Ptqc5DvkEEe1hCq8q1FVX6n+i6JLOAAlkOIZluBrwvC9W5w32Ck12PcbdHmqp/kw6mnG4ba5StW9iZk/Oa4ff4vJBUi2dWjBMgyIUw4fdH6yQ8BT6h4BiRcJkj5AtLHDfwgvaauAkikPX1VOi5akDoFkGV6awJGD36x1HdpTV4uwlPurssRCcgaIU66Fo8FwI1JGwMwPqFKm+kVoNT+gaEp3TbzqA8Dpo0C8M3k/6ZLDvP9Wz/z/VsWjrpiFTK80QuxIeylSM0iaUxeeDhFiEb0FppKi9txXuvrN6Kg7YlVfO6m+eMQo/WoF56HlfLCWJFyNx2/gBp5ALUhKY+SFklSzneImE4RbVogojh8An7TR4QUlX+0aa+CeazNmm74NlRjx/CRm120XqYvMrVb2A6F72tafVFoNa6en0e+1pV6Co1HqpCtfD2thb2rDS2JxIN08zHd+6XohtM=
*/