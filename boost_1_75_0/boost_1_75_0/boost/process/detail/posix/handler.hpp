// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_

#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

//does not extend anything.
struct handler_base_ext : handler_base 
{
    template<typename Executor>
    void on_fork_error  (Executor &, const std::error_code&) const {}

    template<typename Executor>
    void on_exec_setup  (Executor &) const {}

    template<typename Executor>
    void on_exec_error  (Executor &, const std::error_code&) const {}
};


template <class Handler>
struct on_fork_error_ : handler_base_ext
{
    explicit on_fork_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_fork_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};


template <class Handler>
struct on_exec_setup_ : handler_base_ext
{
    explicit on_exec_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_exec_error_ : handler_base_ext
{
    explicit on_exec_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_ */

/* handler.hpp
Xf5fVoQqSl1ghfENTCQCyEgDZ3pFw+7hSqIFSqDUH8qV4UiVB0jXAlWbZiPVC7Xe9x5Or/p5hOoipaR3EeOw9oDqmoCI9GNsr/uIdnidRZy6ciXqa1+DvyjdYq6UYxS8QCYgcR2wQjIWD7p6g3nfp5QgwZIiackRN0EZh3VpwsYkLza5zTmAy5Iyqyhj7aldqZ9ISqCqf/GhnZIx8cMYhfg7p+9xEcOpvCy1eaQyOV9YGNg5eV5Lz5jWF90Wf1yFavQV1wQzHMfb8udnx+6zMGWT8N4zfePN1yU486Lzb93HorS3EQLaTgztwX5cW+q2PKnoklFOvjBSgq7O7r+e+TFb0DaUXQtSFurAKpJmBfbZ4lQ0R5z1c6X15xYhS9p/dL2GquPOCuZEjbIAhrYkcPV0fOHKPagMfR6J4TAW1roqsiALcXWlu143qbKQ/9sDTPi8okBOzlKN+SB7lRsugJn7Vku1PlcqKOX3PncOGh6Bbn80tWYTx1bx6bXSjwgoK2Crk9SRIZXs6kK6DU9nbPp5tn8CSdtfBQRe962AFk4n+Oa+GiyrwMvdVxeo18nOW0WTftlu9lS9flUrfuXVUqKNSihHsgxf8F6i9hobljO1eVduGA+WnfpxOPtl/eVma3fH7u11z9nPTcEur5qQ88Ams+ocm96Wtm30bUgLEl1Q4KbhSs5M/3II+/qpu77NmhbHpVvLH2tdjFkQ
*/