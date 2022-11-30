// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_ASYNC_PIPE_HPP
#define BOOST_PROCESS_ASYNC_PIPE_HPP

#include <boost/config.hpp>
#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/async_pipe.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/async_pipe.hpp>
#endif

namespace boost { namespace process {


#if defined(BOOST_PROCESS_DOXYGEN)


/** Class implementing and asnychronous I/O-Object for use with boost.asio.
 *  It is based on the corresponding I/O Object, that is either boost::asio::windows::stream_handle or
 *  boost::asio::posix::stream_descriptor.
 *
 *  It can be used directly with boost::asio::async_read or async_write.
 *
 * \note The object is copyable, but that does invoke a handle duplicate.
 */
class async_pipe
{
public:
    /** Typedef for the native handle representation.
     * \note This is the handle on the system, not the boost.asio class.
     *
     */
    typedef platform_specific native_handle_type;
    /** Typedef for the handle representation of boost.asio.
     *
     */
    typedef platform_specific handle_type;

    typedef typename handle_type::executor_type executor_type;

    /** Construct a new async_pipe, does automatically open the pipe.
     * Initializes source and sink with the same io_context.
     * @note Windows creates a named pipe here, where the name is automatically generated.
     */
    inline async_pipe(boost::asio::io_context & ios);

    /** Construct a new async_pipe, does automatically open the pipe.
     * @note Windows creates a named pipe here, where the name is automatically generated.
     */
    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink);

    /** Construct a new async_pipe, does automatically open.
     * Initializes source and sink with the same io_context.
     *
     * @note Windows restricts possible names.
     */
    inline async_pipe(boost::asio::io_context & ios, const std::string & name);


    /** Construct a new async_pipe, does automatically open.
     *
     * @note Windows restricts possible names.
     */
    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink, const std::string & name);

    /** Copy-Constructor of the async pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    async_pipe(const async_pipe& lhs);

    /** Move-Constructor of the async pipe.
     */
    async_pipe(async_pipe&& lhs);

    /** Construct the async-pipe from a pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(boost::asio::io_context & ios, const basic_pipe<CharT, Traits> & p);

    /** Construct the async-pipe from a pipe, with two different io_context objects.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(boost::asio::io_context & ios_source,
                        boost::asio::io_context & ios_sink,
                        const basic_pipe<CharT, Traits> & p);


    /** Assign a basic_pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline async_pipe& operator=(const basic_pipe<CharT, Traits>& p);

    /** Copy Assign a pipe.
     * @note Duplicates the handles.
     */
    async_pipe& operator=(const async_pipe& lhs);
    /** Move assign a pipe */
    async_pipe& operator=(async_pipe&& lhs);

    /** Destructor. Closes the pipe handles. */
    ~async_pipe();

    /** Explicit cast to basic_pipe.  */
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline explicit operator basic_pipe<CharT, Traits>() const;

    /** Cancel the current asynchronous operations. */
    void cancel();
    /** Close the pipe handles. */
    void close();
    /** Close the pipe handles. While passing an error_code
     *
     */
    void close(std::error_code & ec);

    /** Check if the pipes are open. */
    bool is_open() const;

    /** Async close, i.e. close after current operation is completed.
     *
     *  \note There is no guarantee that this will indeed read the entire pipe-buffer
     */
    void async_close();

    /** Read some data from the handle.

     * See the boost.asio documentation for more details.
     */
    template<typename MutableBufferSequence>
    std::size_t read_some(const MutableBufferSequence & buffers);

    /** Write some data to the handle.

     * See the boost.asio documentation for more details.
     */
    template<typename MutableBufferSequence>
    std::size_t write_some(const MutableBufferSequence & buffers);

    /** Get the native handle of the source. */
    native_handle native_source() const {return const_cast<boost::asio::windows::stream_handle&>(_source).native();}
    /** Get the native handle of the sink. */
    native_handle native_sink  () const {return const_cast<boost::asio::windows::stream_handle&>(_sink  ).native();}

    /** Start an asynchronous read.
     *
     * See the [boost.asio documentation](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/reference/AsyncReadStream.html) for more details.
     */
    template<typename MutableBufferSequence,
             typename ReadHandler>
    detail::dummy async_read_some(
        const MutableBufferSequence & buffers,
              ReadHandler &&handler);

    /** Start an asynchronous write.

     * See the [boost.asio documentation](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/reference/AsyncWriteStream.html) for more details.
     */
    template<typename ConstBufferSequence,
             typename WriteHandler>
    detail::dummy async_write_some(
        const ConstBufferSequence & buffers,
        WriteHandler && handler);

    ///Get the asio handle of the pipe sink.
    const handle_type & sink  () const &;
    ///Get the asio handle of the pipe source.
    const handle_type & source() const &;

    ///Get the asio handle of the pipe sink. Qualified as rvalue
    handle_type && sink  () &&;
    ///Get the asio handle of the pipe source. Qualified as rvalue
    handle_type && source() &&;

    /// Move the source out of this class and change the io_context. Qualified as rvalue. \attention Will always move.
    handle_type source(::boost::asio::io_context& ios) &&;
    /// Move the sink out of this class and change the io_context. Qualified as rvalue. \attention Will always move
    handle_type sink  (::boost::asio::io_context& ios) &&;

    /// Copy the source out of this class and change the io_context. \attention Will always copy.
    handle_type source(::boost::asio::io_context& ios) const &;
    /// Copy the sink out of this class and change the io_context. \attention Will always copy
    handle_type sink  (::boost::asio::io_context& ios) const &;



};

#else
using ::boost::process::detail::api::async_pipe;
#endif


}}



#endif

/* async_pipe.hpp
pBqoavDpkPcX0kRh15zk5Kkm3JzIul3jzUzr2rPGrA4kk/fRWkM7B2/rPKs9tdMXU8SjMQUqc1m1+c4mjal0d3SR6Yoeu6TpW8Uui2TWs4qXs5p8snNlLeeYPpvp+Zcs1e//qKnJJfxEuTMUvRKUq9kpOq4L5h0s9DqWj17ve6Clbk0etlHaKt6p5Xx5sAws8tnrqDmcYjnb/nvcx2xll0PJ9n5J908jbfPbj3YJeeEAVCXrWgLkShTQ3ptEmNmfkvHckAh/hAgfFnOpMKeTXcs4CNVvDNIIP6OxC5P8iqWQdyzmn5T3rHB3xkmQBCJeQJzJZ+y+vxhGBQs+Mz58L6eaEqEqRZDMgBwdT648iXL552Jec7UIE2nZmsCoMT3ubPRrYX8t7+BwPoadHsHT2q6hMI6rZs+yXDhyGOwPYNB1BxmSIpSHHWGeK5ghr84aIKgU3l5t9/1yJIwXWxBFqH6o4EgtbHRZGlUb2Bs5d8mhweyqLRxAPsEKiIxdnV9OYmWRXW8wH9JQxTKsXxlU7Qb/MTPy/IK0SJOYeBAQbx1miby4cbQX+VkNgWIhc+9ulku7UrhjWrL9XDskecS+cSj8T4U4j4stFPtChSMUm14zc6QxqrGWpeVfzVvj6QV4fPOsmXvUnQ/PVO0+mNpCRoEG32hLc39HgFMDAOP32IcQxJ7ydH8io/+aCHJG0DMB8IDbienDE1lZ/3Fy6hlY84jwP+P+MQEoOEzWAgVeXmknwBxoqKvtWLA8/bP8+f+aJrDvhLkalQyPCNmYPkdC4mO3QmyDi8nIV/JqNoYevlGM/NtO1YD4bb4EyuNH0/71hoXGihPPenQ9j6m8UwoBqsu+lhSbURK08RWqGzxd+lnKgc5yfWku9cvUw1krk01MpI7SjtsmHrDRdWUL5H/YbhPFkWyQH9imMmAENNScDNn26tQaW61aWhPziAdwN5vboE7Ar4ZT74tiptyhIAdWreDfjblX/QqNlpDPTA0iASpm4e9DVIX20pjNwmcDce5/bYN7krMRbGBDEdxE19FEMSbbJcKtEoFVWYf/aM5Hsa2JHEoPiXVxUZJYkSuYjWy2J1numYWe3YKPzsOgheAFK76vVtqrIQH/lCMUO5NJKU1nAbcCsgpri21U6MHhSww1JpUWs73oIxgBwcTCYWd0gH9VCcVn8jmB5Ac/qoco27ahH27uZyqw0MPh9mHaP8Oupjkf95/E++5Frd0hyS0P/IiS1zhWjZqyJ7Yb7BZ4qAQLyZzWxwyR0PUzUIpgaOf3KxcCCLFi/WMv7Q/cfn8CRANmwFR2wBmCY0GbdGN1woahhXkTAqEr+oFUMhfTBn00yU/cy/GRD6oIHNQRm+MgBKvshdP2tivwojPSOe8LGpn4yWSv8uhRu+cYUbrwZ+CoJZRz8ef7h+2/ULn/5mtjjta1K/jCTibsQJ67xnlIB9XsmcQeecawRgjYKrRPa5Ytgj2RIyOpHyRH6SZCmZFjzPWNzY5dm6uyeEhwNj+WFX9kFieDyjaYUr3POCUxZwkmyZY+Q6viG2MrAiRhWgKhapwYePn8AHYbPqjz3GaorTTibjqvSJ5S4DbgKrLl0KsXuHj6qSE9U3BO7qMWSJgQ6DoaMVNIu18EC7DRyLSSzT3EU9zNQbDIMoCzhiDpos17sM5EhGijJJEPNe4Uh9pms8kBoh9Eq+FtzfgCchsFvynC764UDFy55ndhUe+xZKva8AGKxAs7HlWckWH0In+Swijz7a9ZmoENAerWaULv7VuYpomBvHjdGvG+32OJ6njxOWYgk2lEz25RqhRqfNhuI4ZVgt/T3QiJa88HstS2RLsfkuZEuwHbB+M2LsQv8AUUcINU34GNg1ljgW7ZlQQUKDVhqGg7HHtfP+MiQ5KLKO+ON/8vEEvVr7jSRm1/NtGm24VSPwAx6Ju/RUekW4SaClh0ReOh4bnZsWy2tOAFj8Q0N8FxqRAh7jSxTWOJA4qL/X4GZK1doJvyeEA1poCCnWBsItzbXZo09d/7tuxEcGHRPBlaZQiVE2ruyMNICRuN1zUFB4q6lv3k8DV7PmqqzLB7Xv8QFa6CUz0AlDQxk2I1o0Y6Ck0LLkoljHi73DVZRVgVbfnxB8nYh5Fz348Jx1JzE4sGRbEFUQqCk1DSXPUxgp16k5JAnTt46O920T8WSk8j47XLWTa2gSDYrXyg01bW5Faqwjyx2TIoe1CWuHSgDCeibJwZHcNZX5Xa+PDetN1bjFfpVHBqRfQF6v2Zdi7s8ISrMiRySrQCUJgRBvybJ9GxnF/MVx2c8b7OZNT54mQhtl7rWhyn/yBZqKeVu7at7bWd8Ih9t6bvj5Zyh7cSKLEcyAqbUJTRh0W/AuMqXqIdKxGn831smIOa1O/hn5TaUrsPEVK31/uJet5CiO3IRrvEXIp/YMj0N69Nwp+8aXXmBbrBREFpuepxcxWHHMGdahUScvMcYEFairnZR4tcz1ijZjSfgCFixB/LAprdYJ6pNnxrPfw/gw+KNM9QG2J9pXtqiCURtryGT73vD5ytNLPG/GItO6+0FH2w3DiYd4tiGWEaIIc7Td3jtNk2SoUgVKAUtfic7nV2b+VsBi5Sqcl0JU9QngrO2Q4uJ0FgC55HU5lU79GLEuBS3FknZeayKqoBctI03zTvOwmdpjFLRMQXjwfVXOx83MKqGnqKaZkw/EXsMwNq0d9dI7TS1ymyoR54O4qE2wpE1sCIPZPGyUOYTWoI5yKbMB3HsSq4DbTt/Q76gJLromc4VETj4eW598Mb4WVVl8zjwmBEbkS2RMJ1E1VeXc0Q1WdOkua+Ba5+lFqs7R57RvBDpXPFQQbRwOUVVsJXu8NynDu747Cp34efk+nbglT79aq+pr+LYsjt6ndKUUwpULNF7VWJsvGhiT3iVMJJXxKublzl5n08vPmmSKe6JOj5jvOUhjNsGUm+eVUDU7qne0eqVZZ2ZIRuopwOPFoWmLAcKwPlXPwCvfrDxamFb+tb9s8csc+zGOyNy0TWZWp7ULr3kjt28dRR49ldDMzKhnzXJEcTit1QJ2B0BLrfQ2CUlnjB/4MpLC6u+ByWnW02CF87xMCvrI17n8RXtgZnLTCAzQJm7DVQmQnPz4abVo/C2soLzhE9XBVv08B1qrSdjjC4XrPTsHSLyXJDYe/3rD6w1b1nVy9kJFc4/xRV3+/WRQ+Ryz1E+zEFi16/2IBgm/I3+x591SBScYrcoaD+hOegs2uFnLAGRsyMSTilT18bC9XX2DfjMyJjArnBsIjevQlKp1vEAk2cqb3kgxpvXGb64HTSAfCXXd5ujD2MmKR59I34KHTu+qckhmFBGnGwD4bEeEj471w6NkPkxcdwjoDtydMdBhYidzAxX4s+ryM8hZc7xhq30sm3TuzZySc/LJIUF2UtjpBsBbAA8Mu8W1857hasKI1qZR30WQ8HQhQHLfxeaAahhMOrnewnNmpRbVVtPmJJpQJPangIuTEeItDJTW3PuwyPDdeq0WnoFYRkNwybjwxksnUkLp39kvDHqh4EDV2ZmeJEY3jCkU97N4zZrQ5Ee1583qAegxkPrf8lVg7UH8ogu+mwnFhN/WUFDTG0DvhgvwR2DCE/TsBEZ3D2CS4kICTzgRz0xdWK40ANlz9Uvj3sV9CErC6Md8eQasH2vqUciTJS77ePYzuwZne+l3t1+gJbke90bza/nyFlUwx9UvqLI1Q27sraC00FloB3xiYxsbsCmEPDa0TfPZj6CHsj0lHz3mFtzuD6QMBKTXe3CFpGeV0UMeNJuJTGbOO8ibxzbxiVO1Lw1W1ZsCJAgLRrD1MrJZkTi6U5oQkwBrJZxjmy8MogS5CaGpEb+45wxGXXJV/lu/3KIqsDWmdkSfttoelftuXSPvhFmVrzVMtwvPaHk+vkyC0iaSsOVlS0SghxkJ/y2w7D+k2dMsWgoSB6HCnqQ1Hl4FTL25W17OvLHQU86q3ZnA2fNWeRbNoW5kkebcl6yZAkr3b3ppd20aX8e48t6/s/oh+NaFiSJoWQTMFlaWdCl3YAIM+muf/YkVsv76iwtGSjF7Ipsi5wSjuoDWkfWIzIZ8Co6b50O5an3QBDQCIL0Aj8Y/aR9/YbveN0/vtwZyIXdLuG50E/yleoemeVjNXMha+stY16kmbkVGpdLz4hYXtDclibotG0uSJRhPDaNQqIXKLvxCG8+/iaucru0fJqGFyMrrnK/kE3aitdm7Zosq5bhzcEfYE+2cnZ83uXv6rPtxcJ6K9v6QePIwDYFURorIZaCGnYtmgSpeen0GwiHPnHKxCIx0+Hv5HfhkjHQPybo4eJBbm+D3thN5jL7X9l7024ZHYFuGLLOJz0rjGcxN4mcIa8dCTTF2GtaTCxt5AeGwRwJMn6XsIe6fox1SJRcWKPysV1ELavIus3JSLiWSVvFuBBCrVsZqbfoHjtt8fdUmtlbXV330x5cnnVkM5qN8+th4/zl+8NY84rwA68JZjcTemYUOcNeI7oRP0eFSvVBPW5nJyUG37esEid5yRUMKGu43FsuOKNwD2qdsc4LsmfpkCrUF2NbX/o/4LOOgJr0KPIX5i6v0W2YsKXhCXtlKEPNvsVnlCSS3fhnl37oOfNRQP/lcU2Be2c2F7Kv+bv3RUaEHB85wbbhHKUdsWIXtrcx14r6eOe+eKPQMKQxBTq9sBrthq6b3JdsOosY7GMjDxwnjlVIFPUIf3GXFX09kuE8BM3W++pI2XqZXfU3UKKnzDl56VEl7UB5TJd8JG46A25YESfjk7Mt5EhtNu3xxlMqPVofVqfet65cCH0ZkTPnYZDA6X7nNVts2V0suKCsA469qo6BRdu/UTLXc9l/Bs27swE7ZKml3q0vKzIF7Vs8uASTB7y5Uq2ytCOhVywrQ7TDJIlA5fKeA+l6SsGTiFQN6QAzWlytvd8oIS1AlVhmoBvinX953i4N8EwqAso8TllRl25ZVht57QghdGA2sqJLMvw5exI8bIoMyxE1dEyqAt6q7BHu1zJ5pAdAZShHuLspS4E320RuDqcFgfLQ5pruudIxBOIDs31mW9iIQFbyjEUAa+0bFYUfKWiVKz9X8vS1TzFd/NBrWqcvvd/2263EoG0aGD3/kiJdt+QQCu8cSb/bQt4345/6CwR8TTpP1pQRtS5f8ueptVNW3pS9aZPWxrtZBI++mCkv2ZO/lLbjo51QasSVunpdprsgGG762lAUK1GGsE5ggGBR/k1GZvD5GXvgVg8yiIJ9VfqDXTTUe/kNTbYWJA2QYUMzlT2ifIRDcIuyiQ206kvczsHD4GaNKGDsAxOedgSL1ZDi9ssoGTjkgcFGls0qI7L6p8kYv7j8obJf45Ln3lWq7oQa5fr5ppgxfJtc088LV4i05jt3FpPpQqMZV92WC1aELD/1k/ixr5fozmW4lA4C38Hpk2tJWi6w/L94RcXi6UdPbDAyg2dfDTStdcA+T2S6w0GzFOjb4Aoe3TwJQ39KN50mYdubjO8qFu7zodVo/kY35PUMMR4lQOpym3415pwrFKSrl9zkDu8zIgtYtiB/bOwDZGhJisbyNvaaSBmg0mAW4pqJq6rY8oMvGHRry9/h1UJhV4NhV4KNe7K2nEe/mYZ0igZYOQE97U4Gl/HaYLwypt0670Hvrf6HVzj/kzTHFOV52cIWyW6mI82mXVGFrELfgoOEhWXgudBB8Q8e61cWwhGUCwUth153+LlErQZuKt1YYOqIFMmlIMcQnAZLKTNCkVjlL8HkXzwUe20kP9V+mJcoW/AkZ0Yxc3fRUpHtE+lXFCT1YA1gEZ+fTc88ZPAt3Uy03NBKfjsM0kH/SvTkqElnLF7QaJ+xQIaIOezmf5f7BYV0+168HZE6cI8zbgGyjC2d6B32tqHXWU3uYw+YZYhzhuBxJXyJqdfJgllj95r6wlRJlYltK9QKoWcgXAECgK41whJ3IWGOT66bNVVJgMDoLku9B7MAKFEYiDnOKUwiYdU/JXDLlntRkqjWD3onBqtw9xD5Hzb6HqfCOxVzsqQ4mnz5luAejQOmwTX8G1l8Ri/Pz+J5HzkUI7TrnoUainwZQxEKKP4PDcyfdm7A2eEAhWUpMgs2maROEpvYsHcFVJgq9j6Jj9CL7bRfaYyLHEQldl9ao9neT3aMzQLAUtHEXKnVLxPRyv5HU00EUUYhPTO3uNTEEh6mQ9C6KyFkYXKl5sF/p3JfMj9XiZVRD+4zUHvZtpNe2wJ2reNw9LhAn1UFkNYe+SJnWQbM53exZIY67GwFaNT4oxCo2Pnr2v3mJpJp6SB4y1StUCGyiYvIE/IfSAcPxDQM9j5jY7QPdB3a1s54LUxVq5OLJBpmNtDFbpipfZFDtbTaOAuvYT2tSuTq33rtB8nISsL5zSuZtdurIo9jRuQa+16trYJeM2oPvuIBwsFNAYBYfL5sPxc5wZqWaOh+y0DxzwtFevHG5CWoOKYcr0vufX2YJ1j9cfDGLAPz6fkL8vFoQ/F/NSLsSXZuP+YGoskHENCEqMSJ2nq3D9hI8vgquCUpN1+C4YjE2C3BdSFKJmwOiBpGwcljDRg9EnoOOoIS9eV5HzxtA0JJDpKRor9Wg1Jj/JEZgFIbQk9EPe3IHl0BbOak1oClEYRqLZi/sI9POeYdd64bSaoJd4yQvcg5X0i94ohEuCVcs64PdK/nkDZ0WX4yErZ4QUf4oon07LyYAP5IoKXZC+2mJ49WULGuYyZvzeZokYi0hkGkvWk0Q9fNs+xHq59F0gb00n5ABN1K/EC5xuKAHx/IZcZmrkj7h+zaPKc2tkxP5pHWp6GEePwt28ss7xbcaCNMdfPct7NeKQdyayzEZkuNTltOLer5a/AvA7F/WdUIjTGr0fmlzPprwdcr2yQbv5gt5JFK0dvSAgUvJML+b+owqMlPVTP8lqc4tyTLCK5CwtknwnOiqNrB4qaxLtW2BtIY69ywxdjg9+bfto+pA+bQdoxQJd+WrpJH9rU/SmaZ3aslgU5WtV799/oiyyMiEWYqWdhTW8y5WzHpIKGz47NFrKa6vyZtIs6DtzMdO2TSNVLa9RkdDuTKFG9cwm1CuN8JNIBMWoDu7bAO794A2RIDt5bw5YNcEaIRGDuqqHhQQBGFns56KYAUSwlNK8ldAmif8ynRfHPZAMzFTWB7BayY+WloQhcYZkY8eSg0+EVREIBMeUpXX63dRdgSQFivFoiXujzSSF+2Eir391gRLC+/qreBXA0NLEd24EgYbyW4tt5iQwo6/iUGukWSKBOxNaQSl+kN96AtBHfMsYj8m+cZDe/ULPvXfM1e3dkbIn+SXt12T2a/lF3FTXzOkk3+YJVqDE7TLSj+17mFNdVFNTnKpC6KzoVBWTKohkTLibS0nfPob/TPE5WPbmXyKUswc4cCv86abJt2yqkiwAhh4/KRu9ynCvsNclVd8yCjIbz8uYEvAfd7Eft/Gq5GY2/GqVDFGtwUZ/L0SIAjyn9CO/uDseDiFj0ELF9u/E1hw+3iuSVaqF2bsBC+TJHcgwN0JEIRQPEKk0C/Q/mNjrJmJmY0xyRXml17J5LmahF0/mL18/wxDpUWw4To5diNPOwA404K1hYMDN2eQcFG10IHXPU8fcSEnsy+425
*/