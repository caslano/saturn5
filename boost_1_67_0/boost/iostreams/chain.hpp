// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <exception>
#include <iterator>                             // advance.
#include <list>
#include <memory>                               // allocator, auto_ptr or unique_ptr.
#include <stdexcept>                            // logic_error, out_of_range.
#include <boost/checked_delete.hpp>
#include <boost/config.hpp>                     // BOOST_MSVC, template friends,
#include <boost/detail/workaround.hpp>          // BOOST_NESTED_TEMPLATE 
#include <boost/core/typeinfo.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf.hpp> // pubsync.
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/traits.hpp>           // is_filter.
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/next_prior.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type.hpp>
#include <boost/iostreams/detail/execute.hpp>

// Sometimes type_info objects must be compared by name. Borrowed from
// Boost.Python and Boost.Function.
#if defined(__GNUC__) || \
     defined(_AIX) || \
    (defined(__sgi) && defined(__host_mips)) || \
    (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC)) \
    /**/
# include <cstring>
# define BOOST_IOSTREAMS_COMPARE_TYPE_ID(X,Y) \
     (std::strcmp((X).name(),(Y).name()) == 0)
#else
# define BOOST_IOSTREAMS_COMPARE_TYPE_ID(X,Y) ((X)==(Y))
#endif

// Deprecated. Unused.
#define BOOST_IOSTREAMS_COMPONENT_TYPE(chain, index) \
    chain.component_type( index ) \
    /**/

// Deprecated. Unused.
#define BOOST_IOSTREAMS_COMPONENT(chain, index, target) \
    chain.component< target >( index ) \
    /**/

namespace boost { namespace iostreams {

//--------------Definition of chain and wchain--------------------------------//

namespace detail {

template<typename Chain> class chain_client;

//
// Concept name: Chain.
// Description: Represents a chain of stream buffers which provides access
//     to the first buffer in the chain and sends notifications when the
//     streambufs are added to or removed from chain.
// Refines: Closable device with mode equal to typename Chain::mode.
// Models: chain, converting_chain.
// Example:
//
//    class chain {
//    public:
//        typedef xxx chain_type;
//        typedef xxx client_type;
//        typedef xxx mode;
//        bool is_complete() const;                  // Ready for i/o.
//        template<typename T>
//        void push( const T& t,                     // Adds a stream buffer to
//                   streamsize,                     // chain, based on t, with
//                   streamsize );                   // given buffer and putback
//                                                   // buffer sizes. Pass -1 to
//                                                   // request default size.
//    protected:
//        void register_client(client_type* client); // Associate client.
//        void notify();                             // Notify client.
//    };
//

//
// Description: Represents a chain of filters with an optional device at the
//      end.
// Template parameters:
//      Self - A class deriving from the current instantiation of this template.
//          This is an example of the Curiously Recurring Template Pattern.
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Mode - A mode tag.
//
template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
class chain_base {
public:
    typedef Ch                                     char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
    typedef Alloc                                  allocator_type;
    typedef Mode                                   mode;
    struct category
        : Mode,
          device_tag
        { };
    typedef chain_client<Self>                     client_type;
    friend class chain_client<Self>;
private:
    typedef linked_streambuf<Ch>                   streambuf_type;
    typedef std::list<streambuf_type*>             list_type;
    typedef chain_base<Self, Ch, Tr, Alloc, Mode>  my_type;
protected:
    chain_base() : pimpl_(new chain_impl) { }
    chain_base(const chain_base& rhs): pimpl_(rhs.pimpl_) { }
public:

    // dual_use is a pseudo-mode to facilitate filter writing, 
    // not a genuine mode.
    BOOST_STATIC_ASSERT((!is_convertible<mode, dual_use>::value));

    //----------Buffer sizing-------------------------------------------------//

    // Sets the size of the buffer created for the devices to be added to this
    // chain. Does not affect the size of the buffer for devices already
    // added.
    void set_device_buffer_size(std::streamsize n) 
        { pimpl_->device_buffer_size_ = n; }

    // Sets the size of the buffer created for the filters to be added
    // to this chain. Does not affect the size of the buffer for filters already
    // added.
    void set_filter_buffer_size(std::streamsize n) 
        { pimpl_->filter_buffer_size_ = n; }

    // Sets the size of the putback buffer for filters and devices to be added
    // to this chain. Does not affect the size of the buffer for filters or
    // devices already added.
    void set_pback_size(std::streamsize n) 
        { pimpl_->pback_size_ = n; }

    //----------Device interface----------------------------------------------//

    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek(stream_offset off, BOOST_IOS::seekdir way);

    //----------Direct component access---------------------------------------//

    const boost::core::typeinfo& component_type(int n) const
    {
        if (static_cast<size_type>(n) >= size())
            boost::throw_exception(std::out_of_range("bad chain offset"));
        return (*boost::next(list().begin(), n))->component_type();
    }

    // Deprecated.
    template<int N>
    const boost::core::typeinfo& component_type() const { return component_type(N); }

    template<typename T>
    T* component(int n) const { return component(n, boost::type<T>()); }

    // Deprecated.
    template<int N, typename T> 
    T* component() const { return component<T>(N); }

#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    private:
#endif
    template<typename T>
    T* component(int n, boost::type<T>) const
    {
        if (static_cast<size_type>(n) >= size())
            boost::throw_exception(std::out_of_range("bad chain offset"));
        streambuf_type* link = *boost::next(list().begin(), n);
        if (BOOST_IOSTREAMS_COMPARE_TYPE_ID(link->component_type(), BOOST_CORE_TYPEID(T)))
            return static_cast<T*>(link->component_impl());
        else
            return 0;
    }
public:

    //----------Container-like interface--------------------------------------//

    typedef typename list_type::size_type size_type;
    streambuf_type& front() { return *list().front(); }
    BOOST_IOSTREAMS_DEFINE_PUSH(push, mode, char_type, push_impl)
    void pop();
    bool empty() const { return list().empty(); }
    size_type size() const { return list().size(); }
    void reset();

    //----------Additional i/o functions--------------------------------------//

    // Returns true if this chain is non-empty and its final link
    // is a source or sink, i.e., if it is ready to perform i/o.
    bool is_complete() const;
    bool auto_close() const;
    void set_auto_close(bool close);
    bool sync() { return front().BOOST_IOSTREAMS_PUBSYNC() != -1; }
    bool strict_sync();
private:
    template<typename T>
    void push_impl(const T& t, std::streamsize buffer_size = -1, 
                   std::streamsize pback_size = -1)
    {
        typedef typename iostreams::category_of<T>::type  category;
        typedef typename unwrap_ios<T>::type              component_type;
        typedef stream_buffer<
                    component_type,
                    BOOST_IOSTREAMS_CHAR_TRAITS(char_type),
                    Alloc, Mode
                >                                         streambuf_t;
        typedef typename list_type::iterator              iterator;
        BOOST_STATIC_ASSERT((is_convertible<category, Mode>::value));
        if (is_complete())
            boost::throw_exception(std::logic_error("chain complete"));
        streambuf_type* prev = !empty() ? list().back() : 0;
        buffer_size =
            buffer_size != -1 ?
                buffer_size :
                iostreams::optimal_buffer_size(t);
        pback_size =
            pback_size != -1 ?
                pback_size :
                pimpl_->pback_size_;
                
#if defined(BOOST_NO_CXX11_SMART_PTR)

        std::auto_ptr<streambuf_t>
            buf(new streambuf_t(t, buffer_size, pback_size));
            
#else

        std::unique_ptr<streambuf_t>
            buf(new streambuf_t(t, buffer_size, pback_size));
            
#endif
            
        list().push_back(buf.get());
        buf.release();
        if (is_device<component_type>::value) {
            pimpl_->flags_ |= f_complete | f_open;
            for ( iterator first = list().begin(),
                           last = list().end();
                  first != last;
                  ++first )
            {
                (*first)->set_needs_close();
            }
        }
        if (prev) prev->set_next(list().back());
        notify();
    }

    list_type& list() { return pimpl_->links_; }
    const list_type& list() const { return pimpl_->links_; }
    void register_client(client_type* client) { pimpl_->client_ = client; }
    void notify() { if (pimpl_->client_) pimpl_->client_->notify(); }

    //----------Nested classes------------------------------------------------//

    static void close(streambuf_type* b, BOOST_IOS::openmode m)
    {
        if (m == BOOST_IOS::out && is_convertible<Mode, output>::value)
            b->BOOST_IOSTREAMS_PUBSYNC();
        b->close(m);
    }

    static void set_next(streambuf_type* b, streambuf_type* next)
    { b->set_next(next); }

    static void set_auto_close(streambuf_type* b, bool close)
    { b->set_auto_close(close); }

    struct closer {
        typedef streambuf_type* argument_type;
        typedef void result_type;
        closer(BOOST_IOS::openmode m) : mode_(m) { }
        void operator() (streambuf_type* b)
        {
            close(b, mode_);
        }
        BOOST_IOS::openmode mode_;
    };
    friend struct closer;

    enum flags {
        f_complete = 1,
        f_open = 2,
        f_auto_close = 4
    };

    struct chain_impl {
        chain_impl()
            : client_(0), device_buffer_size_(default_device_buffer_size),
              filter_buffer_size_(default_filter_buffer_size),
              pback_size_(default_pback_buffer_size),
              flags_(f_auto_close)
            { }
        ~chain_impl()
            {
                try { close(); } catch (...) { }
                try { reset(); } catch (...) { }
            }
        void close()
            {
                if ((flags_ & f_open) != 0) {
                    flags_ &= ~f_open;
                    stream_buffer< basic_null_device<Ch, Mode> > null;
                    if ((flags_ & f_complete) == 0) {
                        null.open(basic_null_device<Ch, Mode>());
                        set_next(links_.back(), &null);
                    }
                    links_.front()->BOOST_IOSTREAMS_PUBSYNC();
                    try {
                        boost::iostreams::detail::execute_foreach(
                            links_.rbegin(), links_.rend(), 
                            closer(BOOST_IOS::in)
                        );
                    } catch (...) {
                        try {
                            boost::iostreams::detail::execute_foreach(
                                links_.begin(), links_.end(), 
                                closer(BOOST_IOS::out)
                            );
                        } catch (...) { }
                        throw;
                    }
                    boost::iostreams::detail::execute_foreach(
                        links_.begin(), links_.end(), 
                        closer(BOOST_IOS::out)
                    );
                }
            }
        void reset()
            {
                typedef typename list_type::iterator iterator;
                for ( iterator first = links_.begin(),
                               last = links_.end();
                      first != last;
                      ++first )
                {
                    if ( (flags_ & f_complete) == 0 ||
                         (flags_ & f_auto_close) == 0 )
                    {
                        set_auto_close(*first, false);
                    }
                    streambuf_type* buf = 0;
                    std::swap(buf, *first);
                    delete buf;
                }
                links_.clear();
                flags_ &= ~f_complete;
                flags_ &= ~f_open;
            }
        list_type        links_;
        client_type*     client_;
        std::streamsize  device_buffer_size_,
                         filter_buffer_size_,
                         pback_size_;
        int              flags_;
    };
    friend struct chain_impl;

    //----------Member data---------------------------------------------------//

private:
    shared_ptr<chain_impl> pimpl_;
};

} // End namespace detail.

//
// Macro: BOOST_IOSTREAMS_DECL_CHAIN(name, category)
// Description: Defines a template derived from chain_base appropriate for a
//      particular i/o category. The template has the following parameters:
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
// Macro parameters:
//      name_ - The name of the template to be defined.
//      category_ - The i/o category of the template to be defined.
//
#define BOOST_IOSTREAMS_DECL_CHAIN(name_, default_char_) \
    template< typename Mode, typename Ch = default_char_, \
              typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch), \
              typename Alloc = std::allocator<Ch> > \
    class name_ : public boost::iostreams::detail::chain_base< \
                            name_<Mode, Ch, Tr, Alloc>, \
                            Ch, Tr, Alloc, Mode \
                         > \
    { \
    public: \
        struct category : device_tag, Mode { }; \
        typedef Mode                                   mode; \
    private: \
        typedef boost::iostreams::detail::chain_base< \
                    name_<Mode, Ch, Tr, Alloc>, \
                    Ch, Tr, Alloc, Mode \
                >                                      base_type; \
    public: \
        typedef Ch                                     char_type; \
        typedef Tr                                     traits_type; \
        typedef typename traits_type::int_type         int_type; \
        typedef typename traits_type::off_type         off_type; \
        name_() { } \
        name_(const name_& rhs) : base_type(rhs) { } \
        name_& operator=(const name_& rhs) \
        { base_type::operator=(rhs); return *this; } \
    }; \
    /**/
BOOST_IOSTREAMS_DECL_CHAIN(chain, char)
BOOST_IOSTREAMS_DECL_CHAIN(wchain, wchar_t)
#undef BOOST_IOSTREAMS_DECL_CHAIN

//--------------Definition of chain_client------------------------------------//

namespace detail {

//
// Template name: chain_client
// Description: Class whose instances provide access to an underlying chain
//      using an interface similar to the chains.
// Subclasses: the various stream and stream buffer templates.
//
template<typename Chain>
class chain_client {
public:
    typedef Chain                             chain_type;
    typedef typename chain_type::char_type    char_type;
    typedef typename chain_type::traits_type  traits_type;
    typedef typename chain_type::size_type    size_type;
    typedef typename chain_type::mode         mode;

    chain_client(chain_type* chn = 0) : chain_(chn ) { }
    chain_client(chain_client* client) : chain_(client->chain_) { }
    virtual ~chain_client() { }

    const boost::core::typeinfo& component_type(int n) const
    { return chain_->component_type(n); }

    // Deprecated.
    template<int N>
    const boost::core::typeinfo& component_type() const
    { return chain_->BOOST_NESTED_TEMPLATE component_type<N>(); }

    template<typename T>
    T* component(int n) const
    { return chain_->BOOST_NESTED_TEMPLATE component<T>(n); }

    // Deprecated.
    template<int N, typename T>
    T* component() const
    { return chain_->BOOST_NESTED_TEMPLATE component<N, T>(); }

    bool is_complete() const { return chain_->is_complete(); }
    bool auto_close() const { return chain_->auto_close(); }
    void set_auto_close(bool close) { chain_->set_auto_close(close); }
    bool strict_sync() { return chain_->strict_sync(); }
    void set_device_buffer_size(std::streamsize n)
        { chain_->set_device_buffer_size(n); }
    void set_filter_buffer_size(std::streamsize n)
        { chain_->set_filter_buffer_size(n); }
    void set_pback_size(std::streamsize n) { chain_->set_pback_size(n); }
    BOOST_IOSTREAMS_DEFINE_PUSH(push, mode, char_type, push_impl)
    void pop() { chain_->pop(); }
    bool empty() const { return chain_->empty(); }
    size_type size() const { return chain_->size(); }
    void reset() { chain_->reset(); }

    // Returns a copy of the underlying chain.
    chain_type filters() { return *chain_; }
    chain_type filters() const { return *chain_; }
protected:
    template<typename T>
    void push_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS())
    { chain_->push(t BOOST_IOSTREAMS_PUSH_ARGS()); }
    chain_type& ref() { return *chain_; }
    void set_chain(chain_type* c)
    { chain_ = c; chain_->register_client(this); }
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS) && \
    (!BOOST_WORKAROUND(__BORLANDC__, < 0x600))
    template<typename S, typename C, typename T, typename A, typename M>
    friend class chain_base;
#else
    public:
#endif
    virtual void notify() { }
private:
    chain_type* chain_;
};

//--------------Implementation of chain_base----------------------------------//

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
inline std::streamsize chain_base<Self, Ch, Tr, Alloc, Mode>::read
    (char_type* s, std::streamsize n)
{ return iostreams::read(*list().front(), s, n); }

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
inline std::streamsize chain_base<Self, Ch, Tr, Alloc, Mode>::write
    (const char_type* s, std::streamsize n)
{ return iostreams::write(*list().front(), s, n); }

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
inline std::streampos chain_base<Self, Ch, Tr, Alloc, Mode>::seek
    (stream_offset off, BOOST_IOS::seekdir way)
{ return iostreams::seek(*list().front(), off, way); }

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::reset()
{
    using namespace std;
    pimpl_->close();
    pimpl_->reset();
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::is_complete() const
{
    return (pimpl_->flags_ & f_complete) != 0;
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::auto_close() const
{
    return (pimpl_->flags_ & f_auto_close) != 0;
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::set_auto_close(bool close)
{
    pimpl_->flags_ =
        (pimpl_->flags_ & ~f_auto_close) |
        (close ? f_auto_close : 0);
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::strict_sync()
{
    typedef typename list_type::iterator iterator;
    bool result = true;
    for ( iterator first = list().begin(),
                   last = list().end();
          first != last;
          ++first )
    {
        bool s = (*first)->strict_sync();
        result = result && s;
    }
    return result;
}

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::pop()
{
    BOOST_ASSERT(!empty());
    if (auto_close())
        pimpl_->close();
    streambuf_type* buf = 0;
    std::swap(buf, list().back());
    buf->set_auto_close(false);
    buf->set_next(0);
    delete buf;
    list().pop_back();
    pimpl_->flags_ &= ~f_complete;
    if (auto_close() || list().empty())
        pimpl_->flags_ &= ~f_open;
}

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHAIN_HPP_INCLUDED

/* chain.hpp
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
*/