// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SHARED_LIBRARY_IMPL_HPP
#define BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/detail/posix/path_from_handle.hpp>
#include <boost/dll/detail/posix/program_location_impl.hpp>

#include <boost/move/utility.hpp>
#include <boost/swap.hpp>
#include <boost/predef/os.h>

#include <dlfcn.h>
#include <cstring> // strncmp
#if !BOOST_OS_MACOS && !BOOST_OS_IOS && !BOOST_OS_QNX
#   include <link.h>
#elif BOOST_OS_QNX
// QNX's copy of <elf.h> and <link.h> reside in sys folder
#   include <sys/link.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace detail {

class shared_library_impl {

    BOOST_MOVABLE_BUT_NOT_COPYABLE(shared_library_impl)

public:
    typedef void* native_handle_t;

    shared_library_impl() BOOST_NOEXCEPT
        : handle_(NULL)
    {}

    ~shared_library_impl() BOOST_NOEXCEPT {
        unload();
    }

    shared_library_impl(BOOST_RV_REF(shared_library_impl) sl) BOOST_NOEXCEPT
        : handle_(sl.handle_)
    {
        sl.handle_ = NULL;
    }

    shared_library_impl & operator=(BOOST_RV_REF(shared_library_impl) sl) BOOST_NOEXCEPT {
        swap(sl);
        return *this;
    }


    static boost::dll::fs::path decorate(const boost::dll::fs::path & sl) {
        boost::dll::fs::path actual_path = (
            std::strncmp(sl.filename().string().c_str(), "lib", 3)
            ? boost::dll::fs::path((sl.has_parent_path() ? sl.parent_path() / L"lib" : L"lib").native() + sl.filename().native())
            : sl
        );
        actual_path += suffix();
        return actual_path;
    }

    void load(boost::dll::fs::path sl, load_mode::type portable_mode, boost::dll::fs::error_code &ec) {
        typedef int native_mode_t;
        native_mode_t native_mode = static_cast<native_mode_t>(portable_mode);
        unload();

        // Do not allow opening NULL paths. User must use program_location() instead
        if (sl.empty()) {
            boost::dll::detail::reset_dlerror();
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            return;
        }

        // Fixing modes
        if (!(native_mode & load_mode::rtld_now)) {
            native_mode |= load_mode::rtld_lazy;
        }

        if (!(native_mode & load_mode::rtld_global)) {
            native_mode |= load_mode::rtld_local;
        }

#if BOOST_OS_LINUX || BOOST_OS_ANDROID
        if (!sl.has_parent_path() && !(native_mode & load_mode::search_system_folders)) {
            sl = "." / sl;
        }
#else
        if (!sl.is_absolute() && !(native_mode & load_mode::search_system_folders)) {
            boost::dll::fs::error_code current_path_ec;
            boost::dll::fs::path prog_loc = boost::dll::fs::current_path(current_path_ec);
            if (!current_path_ec) {
                prog_loc /= sl;
                sl.swap(prog_loc);
            }
        }
#endif

        native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::search_system_folders);

        // Trying to open with appended decorations
        if (!!(native_mode & load_mode::append_decorations)) {
            native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::append_decorations);

            boost::dll::fs::path actual_path = decorate(sl);
            handle_ = dlopen(actual_path.c_str(), native_mode);
            if (handle_) {
                boost::dll::detail::reset_dlerror();
                return;
            }
            boost::dll::fs::error_code prog_loc_err;
            boost::dll::fs::path loc = boost::dll::detail::program_location_impl(prog_loc_err);
            if (boost::dll::fs::exists(actual_path) && !boost::dll::fs::equivalent(sl, loc, prog_loc_err)) {
                // decorated path exists : current error is not a bad file descriptor and we are not trying to load the executable itself
                ec = boost::dll::fs::make_error_code(
                    boost::dll::fs::errc::executable_format_error
                );
                return;
            }
        }

        // Opening by exactly specified path
        handle_ = dlopen(sl.c_str(), native_mode);
        if (handle_) {
            boost::dll::detail::reset_dlerror();
            return;
        }

        ec = boost::dll::fs::make_error_code(
            boost::dll::fs::errc::bad_file_descriptor
        );

        // Maybe user wanted to load the executable itself? Checking...
        // We assume that usually user wants to load a dynamic library not the executable itself, that's why
        // we try this only after traditional load fails.
        boost::dll::fs::error_code prog_loc_err;
        boost::dll::fs::path loc = boost::dll::detail::program_location_impl(prog_loc_err);
        if (!prog_loc_err && boost::dll::fs::equivalent(sl, loc, prog_loc_err) && !prog_loc_err) {
            // As is known the function dlopen() loads the dynamic library file
            // named by the null-terminated string filename and returns an opaque
            // "handle" for the dynamic library. If filename is NULL, then the
            // returned handle is for the main program.
            ec.clear();
            boost::dll::detail::reset_dlerror();
            handle_ = dlopen(NULL, native_mode);
            if (!handle_) {
                ec = boost::dll::fs::make_error_code(
                    boost::dll::fs::errc::bad_file_descriptor
                );
            }
        }
    }

    bool is_loaded() const BOOST_NOEXCEPT {
        return (handle_ != 0);
    }

    void unload() BOOST_NOEXCEPT {
        if (!is_loaded()) {
            return;
        }

        dlclose(handle_);
        handle_ = 0;
    }

    void swap(shared_library_impl& rhs) BOOST_NOEXCEPT {
        boost::swap(handle_, rhs.handle_);
    }

    boost::dll::fs::path full_module_path(boost::dll::fs::error_code &ec) const {
        return boost::dll::detail::path_from_handle(handle_, ec);
    }

    static boost::dll::fs::path suffix() {
        // https://sourceforge.net/p/predef/wiki/OperatingSystems/
#if BOOST_OS_MACOS || BOOST_OS_IOS
        return ".dylib";
#else
        return ".so";
#endif
    }

    void* symbol_addr(const char* sb, boost::dll::fs::error_code &ec) const BOOST_NOEXCEPT {
        // dlsym - obtain the address of a symbol from a dlopen object
        void* const symbol = dlsym(handle_, sb);
        if (symbol == NULL) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::invalid_seek
            );
        }

        // If handle does not refer to a valid object opened by dlopen(),
        // or if the named symbol cannot be found within any of the objects
        // associated with handle, dlsym() shall return NULL.
        // More detailed diagnostic information shall be available through dlerror().

        return symbol;
    }

    native_handle_t native() const BOOST_NOEXCEPT {
        return handle_;
    }

private:
    native_handle_t         handle_;
};

}}} // boost::dll::detail

#endif // BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

/* shared_library_impl.hpp
o2pfx8mlFcFr5L/HFDIOlPjzMab6MIAYcl/RaJ5vI8GnbSWmIMsDzqHLRO0QzarUwdG4hffc5TRke19ukvSj77RpAx442kizv/uOHHK4ObgKEKe/9pjZ+OfYwY8Z/O0opz7D9yKl4V6zmWt4DGCUQP8uqofSWl+cMBkrb/v2G8CQb9F1OM052ea9ePUCv/s4mCA+lSTp4r7tavCjvwPykF7a3BBe2PFvMI43ymbGJ+W4nr8baqs0oWCq1ng7wCFLISeXDdM0s2s9cGpSh8b+69CExrEnKUEzI9GMaiU7zEn/XAtJz2dp4ZlHQnyZGRokfVk5kkXZgvj9KxqNPYnO5cjqOTyvKtQYZ/gisXYgVHT0Snr7gcl2Flf1OCkjP7qu8S2H+s0EZVfuxMY0d5+zokjoGpY4Ute98tUG9/oE4/IVk3tqTsC0XiJi7eQb1Ca+ggmaibmdlh43NXdVLz2XTNUbxR64lnFUpNouPO6a5U4sZyGSVSSh4pFY/79IHIVvJ9FaHoWriQiOW6zXRty8W4HOuYxCsTGGO57GtNIBrk/5XxA6fK91SOfqgAj21gYN9K2RRnsFhz/w777OBEx9bJhW6knvah8RdV9MzX/ILI/e9vyK6Qo7u3C8a8Ja1QOcH5Jl7ZlD9yczrmBVKm3Edq1GI442bNk3VkmrYkxAK455EHPG4NX2/QfIKckrqhxYsxQ6YtbB67G3uBFbdImvwowDgulsEq8c5e3ckiN2CSoWHHwOuCUupJWUwCSzvE+1KdchyxKS3FkeI6H0tFUFpZzYOrYciN1Bb9/6uXI4dfxVTXpPVtvAvrbI+Xu+kL3TJVmuNYYAXCjJWULX6JWYngorByEO2/wOox6ydjK5X4SA1kW8Kg+pSGvxqz2GS5yPDyDs5IBWVwciTxVmz1CLniSubYnqhltJZu+GpHBf5kreKRss+0y76GFSi7XszyHGUipZSXO3fac6lquXoeiVaFSNdR7ek+qLDpTRo+uVGJajdwsPk3V/VeizzQNdAtQK+nc4xl4/e1bzsEHfC7T9oNKGp6CdLpJVcty9ZGpY5oqAPljvUa5AcBhUWD3vzM7nbcEqH6PDtkaOzxH3Q2VTYBEAKOkU9MgY9pqgn9kRWMyZ8KJmxet+JL4md3PghH0qpAL46VfXO7ek5NmpuDqSA0CTB+xazD5mnFT9ihgYja6Prup0WqhyCjjZW4r0BQAqFnJ9OL4lDooVxvUsC/V6tbhAYuxXslSVS6NU8YRiRG9LuFyByEZVp6+2OeYdoy6ThppVzkIThwHqN5iiOe1N0cv1mBaRcOwtZ+/qE6svKBM/V2x6ec5QleyCZp13ZHrJC4SJ7xJiJtyrO8vb3TQhy1vPVQfMingrXGbwSIolGOJCCPgMIOxC1Bc7V0J8D+yrqxOBouDUDOaiY1Bv5F1srGRf1mOqSK9B8jeUA2nFnopazMCMqxErb7gd0vAKbYFGZz65ZSePwwHN5pZQyFsIOTKMaElnqerhg9N0xKLhKH4/c0zaRpNGNZI3qfQ98HnBCqCf+a4/PUPwj0YxVZMBGl65ZS0JnyjPT7ZDZbusNBUYYmEAPNRz+KUCTrjh+EcyKJNIOp8JIlKui24CagxRYDvdrcK+m2reAavUDLtUziU7cU41csYT7vxb9gQjrOJ6cYDMmEzR0ucPgFDcIJdEuC9hHj4AECPW8UVvTjhbwi6W9GIa/WNEl5RDC2SZJgdKKh4EW71iezZ+tpXt8wW2rkEa9Py+eXmcr/BNzQTha+uR/fqLRwBhyc7wCJth87nRyh6cEv5h8ms+Sy9bnbLhCKyzMUge/TtwUjkBRy5Zs9WjdQivhta1D9bnKSFgqbxfMNdHIzoa4NJyXFDb+KbxEMC5pmk+Hqn9pbKVLGYqf2inp1msFzXsZP3buma1426MQ7IN9OZ/Qk73ppzsnH6K76AzMxQ2A4HZoFKDTYrgS2JHoqHH+DWE6/jnAh88sWNihTP208yZJGhmlsp65kJ6JxsgoK5CHvzU8tfDaoG7KyyuPE/qLdJLPkmAGtD7BdlooqHA79faFWPxu/jZYM1lHiY6VBUS2CkIqjTXS+ALO08iJQaVBpqdg+1o1UtwEVkvL5dR6KMwWUhzqNqIdHkqcvCIdsuLZZ6F8sonWqKQPa8M2i/+qvz3nFnNp61HvUrylA+54hhENsO2YUxioTEKoV49w648hs4FRLXm3WdEokYyDh8ln2eHx7oYINQzB9z/mBWMkMgmNAiO/SRGfLvoZEfWxshtr4ZmFSrN/IZLU6/DTAM1V5AkWCMyL2zntz6HWMfY7HamOQuCPkyv5485774zqogfhttqHtzHe6DnpJrZle0SNuvWFLxU5UjaQSobkwztsy8r3O8VwF2e3iDdtMYG4hI1Z+OcXW44feXPNBuPQawL2nK+Fid4C9PwWP+xLS+WdsJPORwxssJ1PrjiyzaqW+K6gG+c2ZF03AAwKOYlxpovTr5056y1r0lFlYSW7yWMi2M6i2TrisZlPzn5R6o5l8xQJ+5Ra02sCK0ZNHM2GYevb6FRJWkIfAVoiqOw6tBmlzigWC87pcfE1y0lm7bM1coJejVntUX1fUcfpY5dJyh0NuJm0o57xQELsFjdDBVwJj3PZVeAsG3Op3qht0jp3E3egCXF8PUyBmGtR0SUxKRSpSIMpdX0ZCm18o8tNv4XDZPTGHoKP7/cSFezVZEzVWFRoLbvVb1yV4li5Y7WAwjwapHruoxLynWjPzKku501kyAqsD3M0ltlW7cBNJPVqaH/AbcY/oNX33Ae1aWjZ7s6Vv1f81wmzDFgxQ40e+rr8bIx6NQDXp2qbb5uA70UKXMdGTOHcGd99mhtTpDRcGnBQk+JKoRfsAThwUJXCFfytlYnUiBeyxiO1sUk3UXiWzeCwjAcMSUU8pZYNz5QpAkmm77ITppKhzUEGmPYsrKk6jGS6DBknGpzdC+H9EGNf4zmNZULlzuCYavdUmSlQWAtW1NXbaLlyra8VVVEIteXCH6kW87IeYuDC7haZnht8lAMJhXNqn9M7m0Je3bUEA7z9qvpNCkgIQs1pSRe9ZwaqyWZLMDVx2dv5fy9sScPJ1OuNHNSFHWLDzSyKObIvF4yrJzrhoNJgSrIWOBjAQDTal4+4MtF3949g5QWNBXVzwP9i1slfNQgfKmreFRkmthCqRVlHZYFazMZmgFCNW03SJHZrf79bagnU38ZLkmooxzldYjVwBnfE4aTBXOzGM9Je47u/ZzWRKqXBFttRjlr7aH0xTQPsxNOd6WDwZvGIdC2auuY/f6bd7XcJshNqbLNILWpvbz6bv1OqJFTtzBDnTHGhYgtKKJv/Q2NoG2yp0OOanzPSGV0At3ImLgLr/A9EelScKen+avx1h41ssWGUC5fDnAntJ3VobFwqLkLNPpvwE6hqLRv1rB10OGFeBV9UCtRhEvitSf2JopI5n3745s57EkgwmWSolD1gbXNP5ead69AFoq10jPsQOsTVdr/ELJje38Tq0B257vXNZF3zL3qrGYOc6kkhgJE372CiioCFJsAmeNVq3G9fMMSY/mKC+Cp2XOW6SkPxg9/hhjW0/v0sXp93brty037kXAms0j62XXtA6/QY4ghf4TrlhgWLZ7thYBmvWk+UmKJf7KEuxTk1WrhZW714zQzniI2FwGMVFaU0KSWv1tF4OG570A7RDatryDpBvCjo+awvc8dCHfOVjk9tcplbn+o51I6gNRTRjGCYppgF2eSt4KYm3kT9h1yY5gqbVHQKIxHX5yWmfNhn9yCU3Zm1Fq07dZLL7OSaOg1aDgU7z3Zw1gnjlUGVDLjzhRbZSpNfPEPOlakRhz/BQuHUbaNa7WBZ8V+fIgQCGtlaBDgXPQX6G/jwchYS43fSh54bz2Gx0C+90xkx9VIV0uM44vvfxlNcCzIjLvBHH8pPWm6G71rbkdV2Hu04L+pvCKVbXJ8Q5XBO3lCl21y9qQsjnH0xCziZu/MnsvKsit13pjduRRf2l1anqGAef3aW8hbUrBVFqh0c2xFtYAqE1fAypiryLq2LkdxLe7w1FmxvdATwXIbwFT2zVp3GKC5d6LHBiH/Q5ws8U/8QIFLxkF7a/8WhgMcCXKNovRZ1REUEn+TWNw+iWM70JRxvBwmbCW7Bad/GvslfOd+Y9Ar0xADaLEzxh+xJP7sssbBiJVqo/h9uadnLunyEAEXaSSzY9IL6Xe6TmJsIWjGtR28g0hJN7b+Bo2g7JrPJk23HIepxhnPC8n915ElYyC18/l4Puh7yfmINykJjPCPb2IQdpbLke3M0+rhS6586RLwBQsHhdo2HnErtUp02XKeqcU8JXl0edTzJwWw3o49TjQcP0cBBydTLawtsqUf5hbt6M5262khywFNZ92mqA4UZyaMYa6i8rzeg/OS92c4sJ19WRLfxvz9NAWlxlXj531v15xYldoTA3s5UjeBKUq03GfAwUE6eKFDtVmcWkMeQWI+8sSKVCpSg+XqHsm0ERUHJ1t5vYGlboZhVg5BHRMNy5AmsDWrM4HlwEYdx2fEcaOnYNompAzJhxdIPFyU6jPbVtdXkcvouCnjNvGLcDOX/XChKcPUvXhGFVlFSMwXkT+YJgOR/8pC14uqYB2GJcqd+8B7oGRmJ+Dt9LZaxrqVsGD9JzDqH1sDUVV4nED6dNGku6Fibbnme0JQcewViuFnjTSfV//snKMcIPfid3XIcROI6ljYcrnOSHbCkcdwZAYCasR1gD72dDvOYdJp3BaQb+WkxHGUqSHgo2W2IHmK23gS+GIHMs9RoFKgxjtrHTK9TrM1YfGpP6uzvq9HNK7mdK8ossxXhBFybgwEvrBAFw8P97i/tvB4Ne8AuASOdliBuqGrqdODDUhwHfvgjlgNR4oX2a0CZJgLgJWlAofvqBsQb80NXGtdAK7pVm+pcPO1sHnL8Ubm0NoIHMVxQVgjTYHPwN1WBB8jSJ4s5FlpKYHzqJIQPOd+pgMv93+FaLLXzHK4XNFx4W4vEtehfmyT/iIMVOJV+KGcLuZTuB20sGYIhNND63laxso1exxn/ve1gwn2Bg2L25EO/gFJfBPmZVJVfjmPxdznO5AilGjtN6TVULw7Y6+rk5L3G0HejCcIcd4pOT5NdX7LtMOF4OoNp7Y6iE8b1C/aaWf/tglvtvBiPp1uD8h+2pNVbrzeD76eQCoSGsvUkndFJiJ1Zw77le5lrvi31fDC3fh4/qM6kTtKLBNi5U1tDtUNvL2J8f9EHvn+MGB21rbjrfId/K8r2i+BgS47ER3U4POjB/I7KLbuhzn67gZH5LacQjiFs+egBrKavL5QcANWMpTQq95OwH5zw4JIXsKQz4WYQSTaa9HQgzPKfl93i1b3Frq9kqZqP9NIGvwFVxftfp/17j5M8QB7fe5UfJUqXOsYt/868Ob16stHct+ke7OaJRb8TX+vnAMgjucmV14q0aH34ObYWbkVxaEyyz0qAfO/5UhZnDSVvXZpGJlUqBtN6vmJogNtJNvTBieQ/IzVcxP65pIPFGclbqT6cHD2+touZn1wZM8hfTWJumoG3DkyQ4MfORfeVwJbhfDhSf+M1VQa9q2WX18pZXY0YxBAzXREJDn6eWgbTzQh94sBDb6alB/plTTuZu4q+0Jabbdx4IpQ5AEHiFWNjZm5tMoQXcEz1Tbi9A2BRtdhwh26i9XlyWNowjwcxKauiFY/GWpNOBskG1qotMHfT6sGXwopSAbXemNfZe37zHOoYo+FsiJtRvK6jtvjFM5lzNhms5dZ4tD3Wg3DPbh2npgEAtdKHF+SLL73JL28tB9WpjWrKr3o9xkPXNMvZr/Jx7AaUweTQUGZTrkNEoTHcVmGPYoICsstOcXk4bTQ1I0EWPI3oTKmPqPnFMsQ5sR9VJNNJBwSTuIJhADxFQf4J3QU//vi07tSdMb2f7B58Q514rqMtllPgSws1U/mpyUSEYt3Zf+dsSKiPFRwBeEHyKscBbN91dtLsNlcsQhaKoSerXniKWCLv9FnlGg4WI+yZVsqBGhmzQrmNUX3Q0J8aVuRg2A/AkfoM+NM80hLepWa6FWhwoa+GLv9gsFOVlD2YrxCQDrKAZCXS6W5T/szDzSD2RNCMJWqNpejfs4wd6MllplJIAKOtcmJq5nPbCAvoG7QrbU01eUPWYp2aTpI15wxzMfanJ7uSAOoi/T7cYwJQ2yovgpkkUat5STrqa8I+GEOCG3PqPt/c97ocHoRsVuQNq3t/muoc5iRuiRBxDqsLULnoAKGVg3vjmQzMfdTAExrD6xDcJr0tDGZ99DU0JPViKvx0a1gZ5KljlJk6yk1Sz5rSHmeCcKyIo/1X4+JpWcAO6n+z6UkSjjeDatXKHo8T8pCXqtg0bbw0c/HLj4vsDpKh8ng4r0y4EVKVHsUV5mQEXUS9nifc73wRW1vdL13iruqL16Q0b3POQ9Bo3D/7gfF4EhZv70IqvZaRS5tPANsxf/lA8Sv0CZL9BpOp85Owdyji2aSTwYx4RdlzCwwG/oDLUaGJ/Kfwg+Xx1u23lk1bsXMBIy6jU3JRrYGX4MVlnZvkwLjFMTOfYNBnjfJvjnrUlLCJ96+gW6FcEevX2iAkIi25vp/Pq++Ag1VLf2zcgwdUzaMkaA1oCxycdFym/OJXoHm7MnYv5gwHy3AsGaBVQxzm+75gznkPQFlW9Cq+RtHetvA3tBsqFnKUApwG+yID/bfRK7EGC39T03/VOezTm80eDPZIsbDvyJ3ltmuim74qBsgzZLN9uJrqs0Y0fHn73SvxbUsTIcpW5Hi1u0LV0y72JPAlCpMaZR7XtLFq2fsLU3gnLdXblZnj0WWFc2OPG9cZYXaskqxTDVGW0KSYOuT4e0ZYQMpI8+ow2awCcA/FTQ5+RyB2Z2dDgAdAQCA/gD/AfkD+gfsD/gfiD+Qf6D+QP+B+QP7B+4P/B+EP4h/kP4g/0H5g/oH7Q/6H4w/mH+w/mD/wfmD+wfvD/4fgj+Ef4j+EP8h+UP6h+wP+R+KP5R/qP5Q/6H5Q/uH7g/9H4Y/jH+Y/jD/YfnD+oftD/sfjj+cf7j+cP/h+cP7h+8P/x+BP4J/hP4I/xH5I/pH7M9/f8T/SPyR/CP1R/qPzB/ZP3J/5P8o/FH8o/RH+Y/KH9U/an/U/2j80fyj9Uf7j84f3T96f/T/GPwx/GP0x/iPyR/TP2Z/zP9Y/LH8Y/XH+o/NH9s/dn/s/zj8cfzj9Mf5j8sf1z9uf9z/ePzx/OP1x/uPzx/fP35/Av68zYQq+nxMAtXIwGyKeq9gHvtcHsAc+splUzNsMmUz5aXQKbesN5UfzBwzIj/8rDvGmJqB/NfP/qZdVjNcm8pBPFQ94Y5RkEqys5xVE5FGYP8vR4XOtouykpyNyUCeGJluVbx8jHJbZCY3RZ/n5ansm4t/cKqm1d3bb0zFrHk9logAAiz902+BMNIrrBW+bUmzQbhL8lnEQrFR/6Y3Bdan8OpxlcpGCPIQgqjRfH+hzuCfJlpaomSzH/uxt6OZ3xXCKG/86Q10aaCTqRr6Y+T+pWmr0ZyMR8V+RbWj4h3foHfejU7xcuwYqaZo8nDVpkdZTgmtvTnbtaz4PzABsmPU9SC1wUB2TSi3qidT6po3EKDFTECpmhzXze/QIJVbd1cEsi23zCi0iwyet4cBOZ5FjRYwX/H10UuFrV6BsqlT2H8zaFO+sm+b2O+WuiHQDSxjxKknIss+0c/dP59whmlQOJmB9Y3dfS7+06RIMpA49pLeoCxNieU0PncAmU5HfnhbJTHhxXO715oROf9VesZmCM/wAl9NaVnIVfGbMvK8knFo7AvLAWj6inrZl5LUhdKeGANbBxo9oKCzAbg6uaEm5csO6xxIc3QP1Qok3y6BiKhcqfNG61LGKVqqIEH5RFHkwCz3aCjBBT31DX9DNG7b/0cS4QtUyk/gpKThQxxbu48FhdYb8KR4nhy6PY9DFLDcLbPcK1BfbmQBuz3MrjaJ3RRygD8F1iEu24dTwT9Q/HNV0lXNeYXYjcY7J0Z25xrIaz/0BtcG5GRCH7eLcGnSaGdPvs88thUvrXilxTb+ajpKKgtolS2iyRu4x/Zmt2UKGfQKWSpbY08p/MH/8k4sHGNcaIRvWr4tRJ1LSvbd5/KUBk9u34suAYFul5J2lQRAdC1/AFqJ4aK7GqOj+MgRVCR4zpvTnJSQbUbc0UfPlEgwfsIpull2cS6qmvzCmmt0/OG++p3muu2nsPpLrk/X849gvoOcaJUh4YfKcN2yDTGEqHfZUjEwvyU+/FGil2KNvDcDf+w+MIoOo6JjCzl6znLGt+G+7FSjv7Ob3PpOOaI7VZwbPGSXQ9JtaKDXVd8SdBYSouF26NAmQblYKl7XYLUSd0F9gUADJPDzEQ2BKK4BSzZK+ve/DfTy1GkzV1rNKusnb01ebzMLN8WiZD7oxM4NOMmhXOuMbzZN2SRa6qGlSLbEr598ShvzO1gyjBzIH57tz5ZAoBpc/HTNV8p0XplzL+zubEM7c9HusdllaouWh9/qaGtzUqJLzpYPQs/+qUGcEiVuBEqmi2Xnkbfhr8xcFWaWwE9+6kMO6N49T7Vt6X9iiGayMvCQLkOOPGVEbP6DePWIud/VzwXNEXpwe4kI8yPYrd4J/Y8+iqQFguUe9y45LhMjDVLcN2G7e4P3w8fUtJYy2A6er4wEXa+LpW4VbAB1d4TyX5muLSfpmouE4bAry9wwDHJVYSMzmVjkJb6TWeuMhbnb3nz7OynhLO81A8uZQauaz1eS6jfF3UJe9pP5LrN16/jdsaG84SFbNKV2yy7eVBydvSHxUhaCCBM6k3GdZed7NEF5Ge1lwzypmts2CYdgfR8d7u5UJC9D+ZfnWwiIL3BB9W3IBv/lZuJITxZosmV1zbjPjtvVzIgnp/e9xmfffK2oBIJ09GEj850T2XWIHn6nnxqxTJw3dLbxGtef3sCZ9wyN+peK3pjiQmK/znVrdjnP5sXlvICDRcNpEjkpaSkJX+NC0RnSyKQ7zTeqVE5KGnbodu6kl9alF8edh7yEg3sxFvKRTTfZNa1BudlJdvGVwoeYI68QSxi+1Dln3sQ2h2aEl3IiVlqq+RDD2Rwig+d5BT7/Em6NSASkO4QKpKanRsIJ9TaMwknw/GcPKoE=
*/