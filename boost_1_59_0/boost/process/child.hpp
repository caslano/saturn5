// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/child.hpp
 *
 * Defines a child process class.
 */

#ifndef BOOST_PROCESS_CHILD_HPP
#define BOOST_PROCESS_CHILD_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/child_decl.hpp>
#include <boost/process/detail/execute_impl.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {

///The main namespace of boost.process.
namespace process {

template<typename ...Args>
child::child(Args&&...args)
    : child(::boost::process::detail::execute_impl(std::forward<Args>(args)...)) {}


///Typedef for the type of an pid_t
typedef ::boost::process::detail::api::pid_t pid_t;

#if defined(BOOST_PROCESS_DOXYGEN)
/** The main class to hold a child process. It is simliar to [std::thread](http://en.cppreference.com/w/cpp/thread/thread),
 * in that it has a join and detach function.
 *
 * @attention The destructor will call terminate on the process if not joined or detached without any warning.
 *
 */

class child
{
    /** Type definition for the native process handle. */
    typedef platform_specific native_handle_t;

    /** Construct the child from a pid.
     *
     * @attention There is no guarantee that this will work. The process need the right access rights, which are very platform specific.
     */
    explicit child(pid_t & pid) : _child_handle(pid) {};

    /** Move-Constructor.*/
    child(child && lhs);

    /** Construct a child from a property list and launch it
     * The standard version is to create a subprocess, which will spawn the process.
     */
    template<typename ...Args>
    explicit child(Args&&...args);

    /** Construct an empty child. */
    child() = default;

    /** Move assign. */
    child& operator=(child && lhs);

    /** Detach the child, i.e. let it run after this handle dies. */
    void detach();
    /** Join the child. This just calls wait, but that way the naming is similar to std::thread */
    void join();
    /** Check if the child is joinable. */
    bool joinable();

    /** Destructor.
     * @attention Will call terminate (without warning) when the child was neither joined nor detached.
     */
    ~child();

    /** Get the native handle for the child process. */
    native_handle_t native_handle() const;

    /** Get the exit_code. The return value is without any meaning if the child wasn't waited for or if it was terminated. */
    int exit_code() const;
    /** Get the Process Identifier. */
    pid_t id()      const;

    /** Get the native, uninterpreted exit code. The return value is without any meaning if the child wasn't waited
     *  for or if it was terminated. */
    int native_exit_code() const;

    /** Check if the child process is running. */
    bool running();
    /** \overload void running() */
    bool running(std::error_code & ec) noexcept;

    /** Wait for the child process to exit. */
    void wait();
    /** \overload void wait() */
    void wait(std::error_code & ec) noexcept;

    /** Wait for the child process to exit for a period of time.
     * \return True if child exited while waiting.
     */
    template< class Rep, class Period >
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time);
    /** \overload bool wait_for(const std::chrono::duration<Rep, Period>& rel_time) */
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time, std::error_code & ec) noexcept;

    /** Wait for the child process to exit until a point in time.
      * \return True if child exited while waiting.*/
    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time );
    /** \overload bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time )*/
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time, std::error_code & ec) noexcept;

    /** Check if this handle holds a child process.
     * @note That does not mean, that the process is still running. It only means, that the handle does or did exist.
     */
    bool valid() const;
    /** Same as valid, for convenience. */
    explicit operator bool() const;

    /** Check if the the chlid process is in any process group. */
    bool in_group() const;

    /** \overload bool in_group() const */
    bool in_group(std::error_code & ec) const noexcept;

    /** Terminate the child process.
     *
     *  This function will cause the child process to unconditionally and immediately exit.
     *  It is implement with [SIGKILL](http://pubs.opengroup.org/onlinepubs/009695399/functions/kill.html) on posix
     *  and [TerminateProcess](https://technet.microsoft.com/en-us/library/ms686714.aspx) on windows.
     *
     */
    void terminate();

    /** \overload void terminate() */
    void terminate(std::error_code & ec) noexcept;
};

#endif

}}
#endif


/* child.hpp
aW0kWCa5dFHrI0PHoAX6/BaXudbKL1VOR3LcaxjJM52Hgbb/bJoNmnz3h/pummDPWG4fV8ARk59L710pqh1pbgFpJD8TJGrRymNVNAiTTTwLaIfEESlO2enOS7Bc2sBHHdrelaW25t1eQT/fa0tN9Ome/faukCb+dne/uGeM226VsRg3jyN29JGwdgSKS0FgRN0FRlvpToP59K0lOIfUIl4SFts8wlrx/CcdryEeI80G0NbEui5L9RbxpVSuSOkzIPkIJfklWD0ke0yW0J3/ZcCwE8VqZLAY/nUkU4vhIgz5DoR5Fz3+6tp86xznB6qvB+jsuCN8dXJBTKYC0vJj0ySNmMPpdLfeK8QPesptO9TQ4GDpjKe+opn9anu5vAsATO692nxhcNFsYmTENbE1EKWAfUExXCgjsUhdQVDnU0UGJDaymW5MbEocWowjsvOFnkcKklWXMWTT7N9PqUsOpGLWoend+d+mtyvbSUFK094uUecnoUIoECjCotclX8vxboEDL9QyZyHXrBUp8E6c5709ipjPFczM7CiArTPRxhCYSh0KWiFYCildrm3h1sxn3/3GcRLr0Qq2r557HdxDFC+LoGBlODqZspAcLBvpDG7pifQ+W9zo2b68U6BQKMixi4vybQFL40bv4DDKquqpPe7HpFzCb3n9WbxsWT/ar8EoeozvPM8DqLyYbaxaROjgQrm0oP/PBUNRJF0N/72Ob1fn6tjSk5xlnu3VQjl8vZFpav6A2pZHyAF8Hhb4gkSbo1hZT5iH5Vgy89pFYBf23WnupHHLBqrOchOJAx34xG7uhcotayiHGPZ/UfJ6kcpLwWXZPxskPnUeP+Z2fVgQzi6goYKQhzrYEjcbBgP4WaX8YnI+sjo73SWkg7oQX+r7s1QjUt1F/alNIwyDelm5kGXe1em9r2v58D6rsuZ/oZvlF9ZntS5snkvOGk5TLywLTIaLYrj8SS50uCPQtZRM0HBZ38S4bN0AO+W/1oG5f/W/FDkCiKKK7TLGA2bOa2zGZ2zOan/zDK61WOYQPyiBLKlZZv8Q8l4MBRHdZxv1lrDqiHvtw6rM3Sq0sHnNXqI1Vt0aDpbAw3bnw70+Em9ZJNqDIlTi7PLDO8u7VczB6c4XlmsjZOWe3eBExvxX/Cxu+9f+SSzghxr/PYjaQNQxFmaUiv0EBopZtfosbvGX/Dju8pd9HK9F239GpHV+raCFaxw1A+LXfcCw5iUPo1Q/ZEexgD9pkriUEmNB3HVhujUHsc9f9Vm8KXei5KZlR1DLXwp3oti+S3ej/D9tY+hzw/A5YsaIUZgT0E0PkkxMtWB41ys5W7ErRfefTj9jRbHIZyOUEz2Vou5xgtuLSNO3NS7T81+A71oBcYa0meOyqO+BV2+BFx4HdyBYA45BeXZNRTxffV26rYIda6VAXo4CsnS6w3CMnlLxVuPlUi0HXY7Mbkb8HVo2gLogx1h90XszgJqLz549WjWHKPYw9tctBfcRAZ9+zjqb9AMtR6D0UPMMXtDHinF6rntKDoR4AyJhtRSiFGGUuFOiIxOzzDqbTDBAuaWr6gWLrPMlCO67B45VXjOps703h6YLqLCtjz540uN673wmvf1tNQ05/KlMhrNhOC93IQjX1/vbJAbXDrgRIfxf1NRQ2WqfQF2W5zVQVncjcJeat3z6++qS8lD8uTZ9yUYNSNmCzo/E07loa3snrKRGWpKc7NKb+0Uj9vDukQbjVGaVQ9gNiN2PtOnbIlQ8us5gyQuJct9rVLUS1SsiaeJvupFvbnSrxgMW6qrsnTjX0971dUqxh/1eS9IqAp3NqfSGIzoEQhHzgig6GjrrAfNIYxRL1SQ+9jTpB29OovR2n55RdeThfPT10kY2/GXUU9UefseAdtPyvDDWC010NsqLlpxYhcEGE9MdCPYVu8356+U7Cl3g5UPslCDfYQRxteRjuR7yWjWleAwqSQsj7klWSidTSRY0wMTq/yTl4cOjARLTTnO8M6D0CMi01nqBwyC/rojII8gkjF05lVbLAv3/IxUz8ZxP5cmsaU3vFbuw5sjbGZHMkKQ/ZJRW3VgKyREqns5YhdJwDmBde4XVNbfSPYYmKfGJaZ1NxYQkHrdC/caRYErWk/ewSuhRy4ERjhFITMBy8o6ZcjzN9a9ozX70PRM55Qx/4bn2QVlIaogjwS7jK/nv/r+8NGWn0Gke6VbAqCEznHABtM9yFVAKJTjKIoKaEykGdXm4L6OFcsbxhJlsj5rk8qCqSR6J4j0dWtyB9qqivoAp18nBBlFLDqpCAjvZxeyy4lI/GfH7mBesMgWvXwvuO2NZIGEmeY9kKTxM3IZZnWMjye1N08Q3DG33Hvv6c2dcD+GXrtedqXKOWZYrd3iOUQDRJNBhfU+jOpY1DNuC70ePBkRfjma8J9XyAtoiivBlO+d/EltMm2k9nUCXqwdyb1oJ4+45IapUYySWv9wFZJQqsR7J/1oFhaa1rMPjjXVekBOGpgNFurpjMO7VL6hgcKeuz1BtRl9biTKHltTJZpkxufnpiokX1EGlb0QFyYkxwcky83okbYZF4ltG6wG+Re0g+wUmRln2oiJ+A4PVBWCy+u7rjL9oqFctvn4QPLbRZCNR6KF8et6IDiHaZRcEv6tVnb7fEm24tfI0QXRKj93PeauljDakSPDPnWKIJAflUDsogGTTmg5jXv6FJ2ReKgFb9RwjDH0XdyLC42Lp28nnYNjDJtt99wPMTcetlz9QQG3FwUuwjGdkGByJ6EhTNOSn6XGStC1WWNPuyIB3WSQBKbAt0dp/Ii3UBRUmzGNryHxQt6a7H6+XOh6jTMQ6ceB/bSnWBbsdVvEU22bx8w6OgHdlcqR6yc+7+BtcD7SQO/f12Aezzrza7/Mp70c3Ku6yeYJcYJ4Wptof9pWjli0IIBbhr7ltX3CnHTne1dBNM73MWAa632al9+9p31U83rIv63sc31K9xiAqB+7Widc2pXtBrmSqSVaikEE1RVOMYuAWYkDWj7Co0PjwoN7q20boUtflq8zoUU+UAdSTtNfbnapsrts7YJ22zVS62Chx1vV4PBPLfRdqfWeOlJhflDZU4Fpl4DMSsEyzdpmnSKoCbDGt1hLbRPln40pNDw9zYiTD9vfLW02y3TFV6wCKEQs3Q/mlARIyRTznT6OeNNPfPRuvMix4i5hfZzfdaeYrrE8PCdCdH1rtYBE7nj+8mH751rAyhQaByXRlhfN65+SpD3X4SMOAm8vBJZF1xNWEHKXXCmEhM5N8l5WRFShL9UPoCcfGxEw9jlE+vOVl9PQmv5BTybHHOEi2IgyqGJ4l/OaKKhyn7KPMGEcqJvkXiU7wYVySBAA7Qt/So5WAXQ/p4sw1I85dgNRqROp0oZOGk6nhGJNfiNe/jhQdjmD6U96OP8WQ1H+TH26Y9cukEivpc2o/yUX3BWdQoHpYxnLg2OvFqREkHFDHNr0s0etY7wP3roNA/uyUZuh14SRVdkOoeP4uN5l+necLtAi+fAdj1Y4k/C7ysbhzc0S/5O4PE+A714QSfSOurTgDkYovJBbV29plCVby4fMvILI2ll9FZtGM5FsLhydDSL85IQPGQBfmC7qfkJHPbrnkxNGEGvv0P7xa31zpE61WIVhH2hOFGnMkI7ku7TIex6lF8BAVHP2D4ov50KtAViV1R5gEwfUPybpahVetoHMUpBgnpLKH7UL2LhEvG1TYteBy6YFaHlRXLIWRbb9bfm8g+zeLnXMes344g0OzCU+2sBk/cx333H5oPAaLMnesYTmaKB660zzXHoLS+fXMvn4s0n1ts5QQ3nxUBmuccOEtx8SJya867TCyM3OC3mlO8VnqRtAl7w5HJfxN/DYMW1rmiYbGoHtbWGxG/71RlGv7rw0Y+codKrqPqAEopcB+yDwfS9f2wRDAUM+Cl/E8hxfYWz9p8lfmtPamsVS0YihlWyxQibxrjuFZr006nbqZ/Kd102lmqUn6M/cYCqBxher5w6Q8dXJJgoGkRrk2IcHbzFLnhrNEzHS/Uj/SWuchhaDrITpA3WLbSKDbQ1LBqNPeTsCkDWw3NyAQsd2OQytaiy33RwBSyFdr5e0+eSR2OBq3lMnH6x/uc2NhLhfnR8hsDJ8tGyeHLHhgjBg9te024c92nTOt19LDivWnpOQlm61Lovaks+l4B+Og86jhdu0nMZFo4cWmRFYH6G630MM49VzUQOwZHCZvc3DJ1Ed7cclVGjJ7Z1zzf5p0i5hd+qvU18Wip5eU5A7wzdYCbdaCB/o5NR9nUs+ih2PKEcPezqbbN+lzDxi4wJjqtNssMHbu86PMSDXcYfi/XeXBByvV805QvWDcb0bC3DoltviQ2wKkLNnW5Yj20hz3KO80++xvzNu8rvB7jlPRHSj6L9ZzLKStW6n+1zz3QDgAzCPgp9Ytkyk8hlPqZyDrDEupTOYTirNMG5rNihjYrqmXGNVdjG9n0DTHZfydQ6PetWY5enFG9JLvnDodBGqV+64Ia2Te4nVrtNmCGscengCBIb/IB77vb7tmX7YVnQPMkOz1j4MKT/hFZoyKlxod0lUXZVKbZJ5Qwkl3l97Ki/euxmomI/BDH2m9Uimln9YhnLtkvr7puChUpqJu8CU5ZFGJTryfjhhZAbm/022WC1C4GyWtIAJXE/b2AMolyZwNvY1csWCN7P2vdn93lZcC3exi1TdgRz71mdXR16LBCIPZeUdqXYkxv9LR0T/MfgCOwGHo67XwmSZVKPMH97+dtK8G0f9/SpHtDamltLzy1kfHAeEG4pggEWlBBSWZcDEgHElo+iQ1RVZMlgILRUzFXIle/E+XcNyc1UL22rlRc7tLd1u2c3uoKgkeHg55SWFKwsPDjGG+A+KN7bd5hYcRKmD78/v7G8tkZt00t3tVx/P6WSc152FMjreraP5MyWkEEwXey43JgEg5sP1N3PFOPFKgWfJtkW9xe9UFtmVi8z/PXI8mbcioE2/c6Dal3dtUp9VWSGdTnW6rfdBwNGCJO9+spJZOwZW+f1wjneC7hSxomSDY7bZOdfPoMHES842T/OHuHhwC6F+YddTD8QMIF5bBaTk8R10rW6qyUrn94wMR3xkrUsd+6leEg3oxpTjgNmsiTZY8vLD0xcvDgekB8yYWN9HyXUv7+DoXcHHAjwNl0eJk4Z3W7TRR5J+Y5KHbLVDx0nVta9hsz9KsISU8vGEeH0u1w4CS27LasuB3u7KYdKlIFYWJM5fJTuYd8sN+3WgmLIhzak/TsQv9QAFiDSr+B1YcYQ3EgZmo2adE/+zeF3WdPgB2WUO8fT9TI+t/2nV/wC511daQNVGL6we5vjMFYVEVpR57oljPRMz3GG3mzb7K+RWajknS4lROy6+fTt54vR6Tt7vdiTihQGe+xe27LpakfUsfT+C+3w4kj1gdKAKa4B6j+/fpG8EZA8tMeQILgULkts3BaEF+zMAsc6AUWpf20K7ONIvAKVVDXizlh3DnWrNIBZ+qDTshJm/nEMmdtxtQlBSw0xbhzTC3rfOuu2WYFCJ/6Z+24CNOH4WKr2CDhnN+zTFfqbnsnDtXugo2/bYqadDjMNOGCu3f9YScL0RFtnBhblajN2y/rV/PbCu3J3ZZHi2i2rD1CsM2t/v7zs0Y2h39oznPoa0EvGFEjitSfUvNl3Wm8AUAG1oWc3xE3EzATXTAagy8GcfHSqb6P+RLbzNlx00DDYpYJLZMDZnf1a/4/rWvmRYmYnFutsD8W+fKATEWT8P6vHnLw8qkbhAxZhjZ8z0VUqxElFHd3W33tmqhhh3dObSWhgRpqlH+dQYCu81Ps4USeTquEn54KGVlpgZmbTgyynFOe12JOrkpLXRSNasqJDxlTbAPN1NCiU8IfPKmKFbpGhQPjmfvNZYCIWh72Ncbi9YBT+qqTmxNbH1+WInDrX3JEj4d8KVzIXKhXiTOBdEh1OwKACVKxyGBrwu94saEp3v4ujfrfPPgRDmF2ngNOtbkhNDbwVzoKJ7oKrGm6MbPKQVVi+/LLt31DIsEPXQz6RuB/wqmvZssHhxMmJkYqmiem/LAgE4iwSvD3BvUWZeK0bWjI9SedWzAKaj5LqhC9qr09obkK7/LhyHrxk0BpAFLbPbQG6PV9fda3ntaVzWcH7mVmDs6Ul8yFjirywrqu4cS4KVsNEH+ArsTTn2cbh/WY0F74uRVASuCJkx4h3q6naq1a+CQOhN+rdzjeX9arXQ8v347IW4sgE6rw6IWKlBBnkDwC5l0UnYjgXE8p/wYOmWXJ939QgYtr/XzxIlsZCu6jZirtB7lgXFdKm984qhjvqj8YQGEqFKP57lJgwORDtanD3krbMOouM4lvZR/l6TnfDUHbxRF3TQC18m9emrHyLI6TQGQ73+rtjSfqVFx3k7uR/QcmL57sIXkTNlPp5nco3Fx+U8DSuCjiXN8f5kD73umRZLfY7+FTkzXtQiy6HY3JI4n2rUwBq+oXC96ozZuUGPzfO5FT+eFIN+Jrh/1ZOWLQjz9+eKH1nmKbBBbtzGOzhAgpgYR56nr6KxnB4Ol41jXBX3b1I73mGn+P7O4X2LRYO6KU34MHbyN400/pVD5yDyBH1iLBUTa+3V1pg/3FQBEfHhE/2ZZxq7qeOJUVl7w17abr9veFovO5aneuLoxRfI3A9/fBQO5UJ4y0M/r8D4KFwFz5K/naMbxqqjMA1TvEBhxtAJSql+B0z6Ig8DKnDrkDzCkM+87K15M6K4K4FR0JWNL0wwFi7OQEqNDmL4E4SbosJK7B3jP5aZBbb53tBhwG21vNrChI8B/BP3Un7B7JaF4K6ybTXhmKji2wnlWhwhGZT5rak6Eqt/fgYjdlnRYZ/HA+Mwnpxeguc45qws3J8mVs5Sti113qRzd9ZNdOu9Js5ZKhnY67YyCjxPdbjoDFKTjGR9bGbdQ0+aTtHSk853UqV03Qt2up6WpAtuXezHZ1WPFV7SVD1FcxKSjrm3NGTHduLX8NivC8LKBoneGboS8IY80PCHuU4otxEjBGfPrDVslntBgk66ISyAmuFGk0XxdN66lPfaWoLdCKr670/TjakeYlc/x9gKNOiJ7BVSSDR6LZ414c7V74Cfk3jLdH5fofmDLMj6/xywV2Vy0SpzuicCWpKt6aHWv0lRnlmU6/jAQWx2YqCqAaefODQh1cnb0G9ARfqUAM1MCIlIY8ND7ImiAHBgnzmwYPrzRFuYwLcPy3wniLA9jfQUaBCoU4n6//yHMF6ziiDeez/wV+mNYqvsU3+vzE1bVdDAGgY6sba+cirQ5H5/PdkQV2V54lk9scVvrYJvsc4+TCiQXeaN4Sqf3d4HyqyRazxkgQYJhfCLMRE8ZZ3ZPWaLDAj77OeY66mHq9y6m8a+rCJ80My8xCvkr9M4K2qvyzsrkNortpfONma1lS2etB0Ro2Y9Aru/+YHNm9pHkRaS5/Vtm1IWB0doXL/p5jAFQjGGp+soFN+lP3knWx8SkdfaFFpta4WLbdng57Lx7rRlNnsQ81VOQXYmtbtapxCvq7q1ULVXOnphFH52bHzXUr42u1DSaLtJVnfaF5eCPHoY4kz//k7sZtYzhXdPdf2rNr8KH/skaztga+RtrqR8O5ZSr
*/