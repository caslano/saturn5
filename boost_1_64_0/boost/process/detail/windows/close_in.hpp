// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP
#define BOOST_PROCESS_WINDOWS_INITIALIZERS_CLOSE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct close_in : public ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        e.startup_info.hStdInput = boost::winapi::INVALID_HANDLE_VALUE_;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
    }
};

}}}}

#endif

/* close_in.hpp
5ReXwEumsX2arSzLmhencqvcm3p+rBkyL9mhndJukrX/et6Unuv9mejUI7+qiR9xNj/i7H5Yz8vYEvHE8uNr0TmL62gj3Dyv6g/5dSJC/CGxtn0t94s/Xal3TSmXpdzPI+erMpTQwNBlKKQeGpQeMIPTf3+9lv9+ngh3P1X+ZyLz6r5ayPxv7OK0vs5PKQPnqzLwYhcJj3UnxBtugMfJE5/kQWnI7dfNm/6WZ6p5J07lAD9C6y9iLLpSXzl9WztP3FTV7dtAuS4yU9jVJl3rW4m0z+ns9LBftxtpjTCaYAhH1nQk6P1Jp47NHyfhy7fn0PuPXOZUOX1bTIWtJS5X2fcYn27/xpUn9ssDZUTHvZDdk9uZ4b4zDhedWHseFeSrZ+RIhT1nZeaKDusbcfensGExv1vc2MM6ITpV5Dz6hTz7m9hIbYi0s9XioudNdW5jle6r6KaGaWOHcU3+yLhbNkaNOerxtqGq3R0Gh2PGpFj2I5QdBneWrKN6PvBX/8WFaaf95TBNlUNkUrak7VblLRPZCd2vt5cd0ZeycGsidqp8IJNyQNmQ5yaod0T7K/dInqPm6jla2M2Qv0IVwcmYtynQb0qZLJ2aOz0vR01L0HPbTPs6KVs9t0fcpFNDmc71q9ib+jutGfKdNgOeFJ1OTnWtdm97/nS5+knsOtrWSPJqZOtDHBL7QYZX1XuvUn8c7Kq+x0R1curTiU5GN/WNx3OmtMd/cG6PdT05Cd0EzCu6vxa+HGSqciDvfiF5mq7qR/JJ20217cGZ4a78noiVPfPYeU/Nf95ZyPcu9cvveWTHo+PW7L3kzhMvPd8gsji78ntnOu8tGn4PUec9Nf/7zjzeLfnTq9uj3XNa/7w4bWPjSz8paTftv+8sZOc9Pv/1e3CG20P0O0N1DI3AszsaIubbsPV7pO13c0tH3t9exO0d/O4Z/P0Pnpfcwub/KFu4fW3+d1O/7+J3d9vvXrbffWy/e1u/pS0s57eP36m230cxWcF1+rAlpkyNBbTHSKvuYW9GOB3GwNmwLpwLm8JS2ALOh0fh4mS1Hl2tqS+D/UnnHOSGOtc5Bj4Na8CXYD24C34C98Jj8B14Er4LI/HszzAG7oPJcD/cAj+Az8Fy+ArMIR674Ed+f+DH0CT8A7AB/CvsDr+GveE3sD/8Fg6Ex+EoeALmwh9gPjwJC+FPcDr8Gc52qT0lXQAuhm54LfTAVTASrodRcCOMhvfAGPgAjINPwHi4A1aBO2Ei3A2T4LswBZbDVPgJTIeHYVV4FFaDP8BM+AusAaOoN2rCOFgbpkIfrAbrwD/AM2B9WA82gfVhC9gAtoMNYSfYCGbBxrAfbAKHw3PgKNgMjoXN4UTYEk6B58IZsDWcC9vABbAtXALbwWtgB7gang9vgp3gHbAzvAd2hQ/CbnAr7AHLYE/4POwF34C94R7YF74P+8GP4QD4BRwI/woHw+/gEHgSDoUuD305GAVHwCR4AUyHI6EPjoL14B/hWTAHtoOjYSeYB/vA8XAgnAhHwHx4EZwE82ABvBgWwpmwCF4Ni+FKeAn8E5wCt8Kp8Ck4HT4DZ8LX4Sy4G86GH8A58ACcC4/Ay+G3cB40InhOYQRcCBPhFTANLoJ/gIthfbgENodLYWu4HA6A18JcuAKOhyvhXLgaXgvXwFXwBngvvBFuhuvgk/BWuBduhO/BO+FBeBc8DO+GJ+D9MDmSOhNmwodhA7gFng23wlbwUdgOPg57we1wNNwBJ8IyuAE+D++DL8AtcCd8HL4E34Qvw73wVfghfA1+Ct+AR+Gb8DjcBd1RtL3QC/fCVPg2rAbfhfXgn+FZ8C+wA3wPdoHlsDf8CI6HB2AxPAg=
*/