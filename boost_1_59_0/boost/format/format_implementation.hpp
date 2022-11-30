// ----------------------------------------------------------------------------
// format_implementation.hpp  Implementation of the basic_format class
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_IMPLEMENTATION_HPP
#define BOOST_FORMAT_IMPLEMENTATION_HPP

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/format/format_class.hpp>
#include <algorithm> // std::swap

namespace boost {

// ---  basic_format implementation -----------------------------------------//

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const Ch* s)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits)
    {
        if( s)
            parse( s );
    }

#if !defined(BOOST_NO_STD_LOCALE)
    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const Ch* s, const std::locale & loc)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits), loc_(loc)
    {
        if(s) parse( s );
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const string_type& s, const std::locale & loc)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits), loc_(loc)
    {
        parse(s);  
    }
#endif // ! BOOST_NO_STD_LOCALE
    template< class Ch, class Tr, class Alloc>
    io::detail::locale_t basic_format<Ch, Tr, Alloc>:: 
    getloc() const {
        return loc_ ? loc_.get() : io::detail::locale_t(); 
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const string_type& s)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits)
    {
        parse(s);  
    }

    template< class Ch, class Tr, class Alloc> // just don't copy the buf_ member
    basic_format<Ch, Tr, Alloc>:: basic_format(const basic_format& x)
        : items_(x.items_), bound_(x.bound_), style_(x.style_),
          cur_arg_(x.cur_arg_), num_args_(x.num_args_), dumped_(x.dumped_),
          prefix_(x.prefix_), exceptions_(x.exceptions_), loc_(x.loc_)
    {
    }

    template< class Ch, class Tr, class Alloc>  // just don't copy the buf_ member
    basic_format<Ch, Tr, Alloc>& basic_format<Ch, Tr, Alloc>:: 
    operator= (const basic_format& x) {
        if(this == &x)
            return *this;
        (basic_format<Ch, Tr, Alloc>(x)).swap(*this);
        return *this;
    }
    template< class Ch, class Tr, class Alloc>
    void  basic_format<Ch, Tr, Alloc>:: 
    swap (basic_format & x) {
        std::swap(exceptions_, x.exceptions_);
        std::swap(style_, x.style_); 
        std::swap(cur_arg_, x.cur_arg_); 
        std::swap(num_args_, x.num_args_);
        std::swap(dumped_, x.dumped_);

        items_.swap(x.items_);
        prefix_.swap(x.prefix_);
        bound_.swap(x.bound_);
    }

    template< class Ch, class Tr, class Alloc>
    unsigned char basic_format<Ch,Tr, Alloc>:: exceptions() const {
        return exceptions_; 
    }

    template< class Ch, class Tr, class Alloc>
    unsigned char basic_format<Ch,Tr, Alloc>:: exceptions(unsigned char newexcept) { 
        unsigned char swp = exceptions_; 
        exceptions_ = newexcept; 
        return swp; 
    }

    template<class Ch, class Tr, class Alloc>
    void basic_format<Ch, Tr, Alloc>:: 
    make_or_reuse_data (std::size_t nbitems) {
#if !defined(BOOST_NO_STD_LOCALE)
        Ch fill = ( BOOST_USE_FACET(std::ctype<Ch>, getloc()) ). widen(' ');
#else
        Ch fill = ' ';
#endif
        if(items_.size() == 0)
            items_.assign( nbitems, format_item_t(fill) );
        else {
            if(nbitems>items_.size())
                items_.resize(nbitems, format_item_t(fill));
            bound_.resize(0);
            for(std::size_t i=0; i < nbitems; ++i)
                items_[i].reset(fill); //  strings are resized, instead of reallocated
        }
        prefix_.resize(0);
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear () {
        // empty the string buffers (except bound arguments)
        // and make the format object ready for formatting a new set of arguments

        BOOST_ASSERT( bound_.size()==0 || num_args_ == static_cast<int>(bound_.size()) );

        for(unsigned long i=0; i<items_.size(); ++i) {
            // clear converted strings only if the corresponding argument is not  bound :
            if( bound_.size()==0 || items_[i].argN_<0 || !bound_[ items_[i].argN_ ] )
                items_[i].res_.resize(0);
        }
        cur_arg_=0; dumped_=false;
        // maybe first arg is bound:
        if(bound_.size() != 0) {
            for(; cur_arg_ < num_args_ && bound_[cur_arg_]; ++cur_arg_)
                {}
        }
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear_binds () {
        // remove all binds, then clear()
        bound_.resize(0);
        clear();
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear_bind (int argN) {
        // remove the bind of ONE argument then clear()
        if(argN<1 || argN > num_args_ || bound_.size()==0 || !bound_[argN-1] ) {
            if( exceptions() & io::out_of_range_bit)
                boost::throw_exception(io::out_of_range(argN, 1, num_args_+1 ) ); 
            else return *this;
        }
        bound_[argN-1]=false;
        clear();
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    bound_args() const {
        if(bound_.size()==0)
            return 0;
        int n=0;
        for(int i=0; i<num_args_ ; ++i)
            if(bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    fed_args() const {
        if(bound_.size()==0)
            return cur_arg_;
        int n=0;
        for(int i=0; i<cur_arg_ ; ++i)
            if(!bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    cur_arg() const {
      return cur_arg_+1; }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    remaining_args() const {
        if(bound_.size()==0)
            return num_args_-cur_arg_;
        int n=0;
        for(int i=cur_arg_; i<num_args_ ; ++i)
            if(!bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    typename basic_format<Ch, Tr, Alloc>::string_type 
    basic_format<Ch,Tr, Alloc>:: 
    str () const {
        if(items_.size()==0)
            return prefix_;
        if( cur_arg_ < num_args_)
            if( exceptions() & io::too_few_args_bit )
                // not enough variables supplied
                boost::throw_exception(io::too_few_args(cur_arg_, num_args_)); 

        unsigned long i;
        string_type res;
        res.reserve(size());
        res += prefix_;
        for(i=0; i < items_.size(); ++i) {
            const format_item_t& item = items_[i];
            res += item.res_;
            if( item.argN_ == format_item_t::argN_tabulation) { 
                BOOST_ASSERT( item.pad_scheme_ & format_item_t::tabulation);
                if( static_cast<size_type>(item.fmtstate_.width_) > res.size() )
                    res.append( static_cast<size_type>(item.fmtstate_.width_) - res.size(),
                                        item.fmtstate_.fill_ );
            }
            res += item.appendix_;
        }
        dumped_=true;
        return res;
    }
    template< class Ch, class Tr, class Alloc>
    typename std::basic_string<Ch, Tr, Alloc>::size_type  basic_format<Ch,Tr, Alloc>:: 
    size () const {
#ifdef BOOST_MSVC
       // If std::min<unsigned> or std::max<unsigned> are already instantiated
       // at this point then we get a blizzard of warning messages when we call
       // those templates with std::size_t as arguments.  Weird and very annoyning...
#pragma warning(push)
#pragma warning(disable:4267)
#endif
        BOOST_USING_STD_MAX();
        size_type sz = prefix_.size();
        unsigned long i;
        for(i=0; i < items_.size(); ++i) {
            const format_item_t& item = items_[i];
            sz += item.res_.size();
            if( item.argN_ == format_item_t::argN_tabulation)
                sz = max BOOST_PREVENT_MACRO_SUBSTITUTION (sz,
                                        static_cast<size_type>(item.fmtstate_.width_) );
            sz += item.appendix_.size();
        }
        return sz;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    }

namespace io {
namespace detail {

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    bind_arg_body (basic_format<Ch, Tr, Alloc>& self, int argN, const T& val) {
        // bind one argument to a fixed value
        // this is persistent over clear() calls, thus also over str() and <<
        if(self.dumped_) 
            self.clear(); // needed because we will modify cur_arg_
        if(argN<1 || argN > self.num_args_) {
            if( self.exceptions() & io::out_of_range_bit )
                boost::throw_exception(io::out_of_range(argN, 1, self.num_args_+1 ) );
            else return self;
        }
        if(self.bound_.size()==0) 
            self.bound_.assign(self.num_args_,false);
        else 
            BOOST_ASSERT( self.num_args_ == static_cast<signed int>(self.bound_.size()) );
        int o_cur_arg = self.cur_arg_;
        self.cur_arg_ = argN-1; // arrays begin at 0

        self.bound_[self.cur_arg_]=false; // if already set, we unset and re-sets..
        self.operator%(val); // put val at the right place, because cur_arg is set
    

        // Now re-position cur_arg before leaving :
        self.cur_arg_ = o_cur_arg; 
        self.bound_[argN-1]=true;
        if(self.cur_arg_ == argN-1 ) {
            // hum, now this arg is bound, so move to next free arg
            while(self.cur_arg_ < self.num_args_ && self.bound_[self.cur_arg_])   
                ++self.cur_arg_;
        }
        // In any case, we either have all args, or are on an unbound arg :
        BOOST_ASSERT( self.cur_arg_ >= self.num_args_ || ! self.bound_[self.cur_arg_]);
        return self;
    }

    template<class Ch, class Tr, class Alloc, class T> basic_format<Ch, Tr, Alloc>&
    modify_item_body (basic_format<Ch, Tr, Alloc>& self, int itemN, T manipulator) {
        // applies a manipulator to the format_item describing a given directive.
        // this is a permanent change, clear or reset won't cancel that.
        if(itemN<1 || itemN > static_cast<signed int>(self.items_.size() )) {
            if( self.exceptions() & io::out_of_range_bit ) 
                boost::throw_exception(io::out_of_range(itemN, 1, static_cast<int>(self.items_.size()) ));
            else return self;
        }
        self.items_[itemN-1].fmtstate_. template apply_manip<T> ( manipulator );
        return self;
    }

} // namespace detail
} // namespace io
} // namespace boost



#endif  // BOOST_FORMAT_IMPLEMENTATION_HPP

/* format_implementation.hpp
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
*/