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
+BHwSDOz2dlL/Ij2yPJo14R0gX0rjgOWjQjt1BfFACsN6OOEVA3zeqsMZIOkId5iz3vgEd7X0EhzLxNBpBH3eYadGz58gDw+QD/56tmJXQ+M0O+2vKB02an6vLm9OckQvfdsZ5t9VFKRa18+2lcHl3aMpHNKaZzuuW9sx9z+RrDOosCfxDXiaRr4U20pf46e8IreeoCqLtDy0ic8cPIr8S8Uo/afAFc6482ekGIJ9RZsyHXeTCWvIZqOEjN9jBj34LJwvjM9D1IDzohusL76H6+bZsKCL4TPulHW3aCF4dvUd8ForloNfh9o0f6P85Pxbx+9yhtMGwft/aP6Qx80vYqbHxET6p/GO/YnzPR79CNffyHFTmL7MIHekd7N2yBXeoiriN4DF/RGVPN+AacfyPtIN0ng1Et9jmsQ4PwxBHocsM/CwVPzAUnV5w2PncwGnM72328ivUPgOqpzwDH5r3l3G4Dmm5TrFcx3Lf2assmPTlEcbU2i7KpXrD+kqbhpv5uvaLUL63YJG5x+0FAvaAa96qF/TMA/Id0JxuHIPv15EgQ1lHndAFhwm3s+F/TluQSIL7VnLb4urTcXwz+B/C67AUnh9Z2ArHeW6w/cP8+Y84673Jb+o/lN+6+Tjag6mTpK2zqbOpoZGv8160gWgg62efYDobGZUfw416BAqx31rEDGkgnHtLtIvLxZAryFMyYxDR6HB8cNPxP2
*/