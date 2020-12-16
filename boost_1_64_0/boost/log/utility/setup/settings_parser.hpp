/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   settings_parser.hpp
 * \author Andrey Semashev
 * \date   20.07.2012
 *
 * The header contains definition of a settings parser function.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The function parses library settings from an input stream
 *
 * \param strm Stream, that provides library settings
 *
 * \b Throws: An <tt>std::exception</tt>-based exception if the read data cannot be interpreted as the library settings
 */
template< typename CharT >
BOOST_LOG_SETUP_API basic_settings< CharT > parse_settings(std::basic_istream< CharT >& strm);

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_

/* settings_parser.hpp
/8B67vyb+Er88M0n3wLyLSTfOl02mvLW6Rwj15DPhfIJA4az3CKAycBI4EXA2rQLFwXsBIwGXgqMA44CNgDmABsD84FNgQXAZGAR7c7dBmwOXEC7c7+lXbn7gPWAj9AOXQntzq2iP+1LUTYYdSrpt9qXKmO+PwRGAk+w/vYAY4H7gPWB+4ENgR8BGwEPApOBh4EXAcuBrYHHgO0Zz1fA+bqcLmWB09lu54B0fQpuv+60b9WD9q2uZ/vtSXuBfYDtqa9hCO/hj+M9/HTev8+hXaoi6oWYRztTCxkf7dNQPhbtQdJjtU/zFdvxN8z/d8B44D+ADYDfsh1/x3L4HtiU/vcDzwIXk38F8Cej/VE+FBipaH8Pst/+jvolEAf5ENYP35PkW0m+p0x8+WY+h3o3LtZlG4FR5HOZbEJ24zjRHWiMR37ek8n3ZPE92aZ6KCFfB0U9rGW7fAUYAXyV9fE6++cbwETgetbHq6yHDcBWwLeA7YAbgSKjaKqHcj/p3cr3bgPWAm438VX44ZvKfOYyn3lAvf1rlHNapWj/57G9xTM/DYHdgY05TjYBjgY2Bbp5WwEzgM2BucCWwALghcC76X8PMIHtLxH4FN2NcZzpqVCM4204Xl/C9t4B2BKYAnySv58DdgK+BOwMXEv/ncCOwPfp/gHdz9D9S7rze0TZFeRF8T3qGsJ2xnGpB7AZ8HKjPkDkj1LUx2rWxzMcV/5g6hd9yFdbwfcc+Z4HRgJfIN8GUCr5DpAvEbSWfHEcx+oBE6iPI8kdBngJsD4wBdgZ2Al4PvAyYGOOY8nACcBmwInUKzQT2ILjWEfgYuoNWsp4lgFbAZ+lXpn11CuzlXpl9gDbA/cz/FfAPrpMA7AO8xFumhudYrl/wnL/lN+DvwBj+FvXe5PPeBIkHqvem14cJ3oDI4FXAOsCrwSeB+wDjOdvPb5iP/H1Y3z9Gd8AxjeQ8V3N+PDb+O6VMr7Biu9eCfvdk8zfSubvj8C6tDsaB3ya4/wz/M79gePKs8DOwDXsr6XAQeQ39AnxHPAyRTvrjXBRwCsZT3+gnu508g1SpPs+pvsBpvtBpnc58DzgYn6XHwK2BT4M7AR8BNgVuITpXUa7rY8CryX/V/wmbuD7X+X75d4S3/9XtvO/047uWerH+gnYF6ghnhvcAMwExtDuaxjHqQjgdGAt4K3A2sDbgVH8bkYDl5JvGfAbxPsi8FvgOroznTxPxNiuSOeLTOefgM2AbwD7Sz/21NNbwEzgRs4bdgGnArcA59C+4lzgdtodfgd4L3AH8PfAncAnybcS+ArwDeA64Ea6sx3wrA1pV7SDpRxvllEf0KNmPV1++B4j3wrylZj1dPnhG0G+keQbpX/3ec7i67vfmf2vC9D4Hvp5z2/5nvv4nvv19PEcwBffTeRLIx/8vf3JD9/nHLe+AEYDvzT1w2Q/fDvIt5N8uww+kB++yUznFKbzZvP3xQ/ffPItIN9Ckx6xVPK1U4x/M8g3G9iE9puTgXPZvn8DbMvfen0WM75wRX0WML5CoL7OKWH4DYp1Thn7026N6wPO07/gPH0/03EYeCXwGPBq4HHa8z4BnMzwU4Cn+H07zf72F+CdwM/Y387wO/c5cAX5SoAHOA58BPwz3Y3vB/fROivKL5XtdxgwHDjcRb1ftCM7muuzMUCjHzG+BEU9DmJ8g/ndGQIscmE8PBUlerWgX+v/QqdWWB+3Xq3/PZ1alfVpNfoE9iRB40FzQUtA60D7QV+DYk9HaReD+oGyQPNBK0GbQeUg7S/QvwXqBxoPmglaDFoL2g06Awr7FGFAA0HpoDmgxaA1oM2gk6DIzxAG1A+UDpoDWgJ6A3QIdBaUdAY=
*/