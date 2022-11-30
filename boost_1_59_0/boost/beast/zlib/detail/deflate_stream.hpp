//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// This is a derivative work based on Zlib, copyright below:
/*
    Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    Jean-loup Gailly        Mark Adler
    jloup@gzip.org          madler@alumni.caltech.edu

    The data format used by the zlib library is described by RFCs (Request for
    Comments) 1950 to 1952 in the files http://tools.ietf.org/html/rfc1950
    (zlib format), rfc1951 (deflate format) and rfc1952 (gzip format).
*/

#ifndef BOOST_BEAST_ZLIB_DETAIL_DEFLATE_STREAM_HPP
#define BOOST_BEAST_ZLIB_DETAIL_DEFLATE_STREAM_HPP

#include <boost/beast/zlib/error.hpp>
#include <boost/beast/zlib/zlib.hpp>
#include <boost/beast/zlib/detail/ranges.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace boost {
namespace beast {
namespace zlib {
namespace detail {

class deflate_stream
{
protected:
    // Upper limit on code length
    static std::uint8_t constexpr maxBits = 15;

    // Number of length codes, not counting the special END_BLOCK code
    static std::uint16_t constexpr lengthCodes = 29;

    // Number of literal bytes 0..255
    static std::uint16_t constexpr literals = 256;

    // Number of Literal or Length codes, including the END_BLOCK code
    static std::uint16_t constexpr lCodes = literals + 1 + lengthCodes;

    // Number of distance code lengths
    static std::uint16_t constexpr dCodes = 30;

    // Number of codes used to transfer the bit lengths
    static std::uint16_t constexpr blCodes = 19;

    // Number of distance codes
    static std::uint16_t constexpr distCodeLen = 512;

    // Size limit on bit length codes
    static std::uint8_t constexpr maxBlBits= 7;

    static std::uint16_t constexpr minMatch = 3;
    static std::uint16_t constexpr maxMatch = 258;

    // Can't change minMatch without also changing code, see original zlib
    BOOST_STATIC_ASSERT(minMatch == 3);

    // end of block literal code
    static std::uint16_t constexpr END_BLOCK = 256;

    // repeat previous bit length 3-6 times (2 bits of repeat count)
    static std::uint8_t constexpr REP_3_6 = 16;

    // repeat a zero length 3-10 times  (3 bits of repeat count)
    static std::uint8_t constexpr REPZ_3_10 = 17;

    // repeat a zero length 11-138 times  (7 bits of repeat count)
    static std::uint8_t constexpr REPZ_11_138 = 18;

    // The three kinds of block type
    static std::uint8_t constexpr STORED_BLOCK = 0;
    static std::uint8_t constexpr STATIC_TREES = 1;
    static std::uint8_t constexpr DYN_TREES    = 2;

    // Maximum value for memLevel in deflateInit2
    static std::uint8_t constexpr max_mem_level = 9;

    // Default memLevel
    static std::uint8_t constexpr DEF_MEM_LEVEL = max_mem_level;

    /*  Note: the deflate() code requires max_lazy >= minMatch and max_chain >= 4
        For deflate_fast() (levels <= 3) good is ignored and lazy has a different
        meaning.
    */

    // maximum heap size
    static std::uint16_t constexpr HEAP_SIZE = 2 * lCodes + 1;

    // size of bit buffer in bi_buf
    static std::uint8_t constexpr Buf_size = 16;

    // Matches of length 3 are discarded if their distance exceeds kTooFar
    static std::size_t constexpr kTooFar = 4096;

    /*  Minimum amount of lookahead, except at the end of the input file.
        See deflate.c for comments about the minMatch+1.
    */
    static std::size_t constexpr kMinLookahead = maxMatch + minMatch+1;

    /*  Number of bytes after end of data in window to initialize in order
        to avoid memory checker errors from longest match routines
    */
    static std::size_t constexpr kWinInit = maxMatch;

    // Describes a single value and its code string.
    struct ct_data
    {
        std::uint16_t fc; // frequency count or bit string
        std::uint16_t dl; // parent node in tree or length of bit string

        bool
        operator==(ct_data const& rhs) const
        {
            return fc == rhs.fc && dl == rhs.dl;
        }
    };

    struct static_desc
    {
        ct_data const*      static_tree;// static tree or NULL
        std::uint8_t const* extra_bits; // extra bits for each code or NULL
        std::uint16_t       extra_base; // base index for extra_bits
        std::uint16_t       elems;      //  max number of elements in the tree
        std::uint8_t        max_length; // max bit length for the codes
    };

    struct lut_type
    {
        // Number of extra bits for each length code
        std::uint8_t const extra_lbits[lengthCodes] = {
            0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0
        };

        // Number of extra bits for each distance code
        std::uint8_t const extra_dbits[dCodes] = {
            0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13
        };

        // Number of extra bits for each bit length code
        std::uint8_t const extra_blbits[blCodes] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7
        };

        // The lengths of the bit length codes are sent in order
        // of decreasing probability, to avoid transmitting the
        // lengths for unused bit length codes.
        std::uint8_t const bl_order[blCodes] = {
            16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15
        };

        ct_data ltree[lCodes + 2];

        ct_data dtree[dCodes];

        // Distance codes. The first 256 values correspond to the distances
        // 3 .. 258, the last 256 values correspond to the top 8 bits of
        // the 15 bit distances.
        std::uint8_t dist_code[distCodeLen];

        std::uint8_t length_code[maxMatch-minMatch+1];

        std::uint8_t base_length[lengthCodes];

        std::uint16_t base_dist[dCodes];

        static_desc l_desc = {
            ltree, extra_lbits, literals+1, lCodes, maxBits
        };

        static_desc d_desc = {
            dtree, extra_dbits, 0, dCodes, maxBits
        };

        static_desc bl_desc =
        {
            nullptr, extra_blbits, 0, blCodes, maxBlBits
        };
    };

    struct tree_desc
    {
        ct_data *dyn_tree;           /* the dynamic tree */
        int     max_code;            /* largest code with non zero frequency */
        static_desc const* stat_desc; /* the corresponding static tree */
    };

    enum block_state
    {
        need_more,      /* block not completed, need more input or more output */
        block_done,     /* block flush performed */
        finish_started, /* finish started, need only more output at next deflate */
        finish_done     /* finish done, accept no more input or output */
    };

    // VFALCO This might not be needed, e.g. for zip/gzip
    enum StreamStatus
    {
        EXTRA_STATE = 69,
        NAME_STATE = 73,
        COMMENT_STATE = 91,
        HCRC_STATE = 103,
        BUSY_STATE = 113,
        FINISH_STATE = 666
    };

    /* A std::uint16_t is an index in the character window. We use short instead of int to
     * save space in the various tables. IPos is used only for parameter passing.
     */
    using IPos = unsigned;

    using self = deflate_stream;
    typedef block_state(self::*compress_func)(z_params& zs, Flush flush);

    //--------------------------------------------------------------------------

    lut_type const& lut_;

    bool inited_ = false;
    std::size_t buf_size_;
    std::unique_ptr<std::uint8_t[]> buf_;

    int status_;                    // as the name implies
    Byte* pending_buf_;             // output still pending
    std::uint32_t
        pending_buf_size_;          // size of pending_buf
    Byte* pending_out_;             // next pending byte to output to the stream
    uInt pending_;                  // nb of bytes in the pending buffer
    boost::optional<Flush>
        last_flush_;                // value of flush param for previous deflate call

    uInt w_size_;                   // LZ77 window size (32K by default)
    uInt w_bits_;                   // log2(w_size)  (8..16)
    uInt w_mask_;                   // w_size - 1

    /*  Sliding window. Input bytes are read into the second half of the window,
        and move to the first half later to keep a dictionary of at least wSize
        bytes. With this organization, matches are limited to a distance of
        wSize-maxMatch bytes, but this ensures that IO is always
        performed with a length multiple of the block size. Also, it limits
        the window size to 64K.
        To do: use the user input buffer as sliding window.
    */
    Byte *window_ = nullptr;

    /*  Actual size of window: 2*wSize, except when the user input buffer
        is directly used as sliding window.
    */
    std::uint32_t window_size_;

    /*  Link to older string with same hash index. To limit the size of this
        array to 64K, this link is maintained only for the last 32K strings.
        An index in this array is thus a window index modulo 32K.
    */
    std::uint16_t* prev_;

    std::uint16_t* head_;           // Heads of the hash chains or 0

    uInt  ins_h_;                   // hash index of string to be inserted
    uInt  hash_size_;               // number of elements in hash table
    uInt  hash_bits_;               // log2(hash_size)
    uInt  hash_mask_;               // hash_size-1

    /*  Number of bits by which ins_h must be shifted at each input
        step. It must be such that after minMatch steps,
        the oldest byte no longer takes part in the hash key, that is:
        hash_shift * minMatch >= hash_bits
    */
    uInt hash_shift_;

    /*  Window position at the beginning of the current output block.
        Gets negative when the window is moved backwards.
    */
    long block_start_;

    uInt match_length_;             // length of best match
    IPos prev_match_;               // previous match
    int match_available_;           // set if previous match exists
    uInt strstart_;                 // start of string to insert
    uInt match_start_;              // start of matching string
    uInt lookahead_;                // number of valid bytes ahead in window

    /*  Length of the best match at previous step. Matches not greater
        than this are discarded. This is used in the lazy match evaluation.
    */
    uInt prev_length_;

    /*  To speed up deflation, hash chains are never searched beyond
        this length. A higher limit improves compression ratio but
        degrades the speed.
    */
    uInt max_chain_length_;

    /*  Attempt to find a better match only when the current match is strictly
        smaller than this value. This mechanism is used only for compression
        levels >= 4.

        OR Insert new strings in the hash table only if the match length is not
        greater than this length. This saves time but degrades compression.
        used only for compression levels <= 3.
    */
    uInt max_lazy_match_;

    int level_;                     // compression level (1..9)
    Strategy strategy_;             // favor or force Huffman coding

    // Use a faster search when the previous match is longer than this
    uInt good_match_;

    int nice_match_;                // Stop searching when current match exceeds this

    ct_data dyn_ltree_[
        HEAP_SIZE];                 // literal and length tree
    ct_data dyn_dtree_[
        2*dCodes+1];                // distance tree
    ct_data bl_tree_[
        2*blCodes+1];               // Huffman tree for bit lengths

    tree_desc l_desc_;              // desc. for literal tree
    tree_desc d_desc_;              // desc. for distance tree
    tree_desc bl_desc_;             // desc. for bit length tree

    // number of codes at each bit length for an optimal tree
    std::uint16_t bl_count_[maxBits+1];

    // Index within the heap array of least frequent node in the Huffman tree
    static std::size_t constexpr kSmallest = 1;

    /*  The sons of heap[n] are heap[2*n] and heap[2*n+1].
        heap[0] is not used. The same heap array is used to build all trees.
    */

    int heap_[2*lCodes+1];          // heap used to build the Huffman trees
    int heap_len_;                  // number of elements in the heap
    int heap_max_;                  // element of largest frequency

    // Depth of each subtree used as tie breaker for trees of equal frequency
    std::uint8_t depth_[2*lCodes+1];

    std::uint8_t *l_buf_;           // buffer for literals or lengths

    /*  Size of match buffer for literals/lengths.
        There are 4 reasons for limiting lit_bufsize to 64K:
          - frequencies can be kept in 16 bit counters
          - if compression is not successful for the first block, all input
            data is still in the window so we can still emit a stored block even
            when input comes from standard input.  (This can also be done for
            all blocks if lit_bufsize is not greater than 32K.)
          - if compression is not successful for a file smaller than 64K, we can
            even emit a stored file instead of a stored block (saving 5 bytes).
            This is applicable only for zip (not gzip or zlib).
          - creating new Huffman trees less frequently may not provide fast
            adaptation to changes in the input data statistics. (Take for
            example a binary file with poorly compressible code followed by
            a highly compressible string table.) Smaller buffer sizes give
            fast adaptation but have of course the overhead of transmitting
            trees more frequently.
          - I can't count above 4
    */
    uInt lit_bufsize_;
    uInt last_lit_;                 // running index in l_buf_

    /*  Buffer for distances. To simplify the code, d_buf_ and l_buf_
        have the same number of elements. To use different lengths, an
        extra flag array would be necessary.
    */
    std::uint16_t* d_buf_;

    std::uint32_t opt_len_;         // bit length of current block with optimal trees
    std::uint32_t static_len_;      // bit length of current block with static trees
    uInt matches_;                  // number of string matches in current block
    uInt insert_;                   // bytes at end of window left to insert

    /*  Output buffer.
        Bits are inserted starting at the bottom (least significant bits).
     */
    std::uint16_t bi_buf_;

    /*  Number of valid bits in bi_buf._  All bits above the last valid
        bit are always zero.
    */
    int bi_valid_;

    /*  High water mark offset in window for initialized bytes -- bytes
        above this are set to zero in order to avoid memory check warnings
        when longest match routines access bytes past the input.  This is
        then updated to the new high water mark.
    */
    std::uint32_t high_water_;

    //--------------------------------------------------------------------------

    deflate_stream()
        : lut_(get_lut())
    {
    }

    /*  In order to simplify the code, particularly on 16 bit machines, match
        distances are limited to MAX_DIST instead of WSIZE.
    */
    std::size_t
    max_dist() const
    {
        return w_size_ - kMinLookahead;
    }

    void
    put_byte(std::uint8_t c)
    {
        pending_buf_[pending_++] = c;
    }

    void
    put_short(std::uint16_t w)
    {
        put_byte(w & 0xff);
        put_byte(w >> 8);
    }

    /*  Send a value on a given number of bits.
        IN assertion: length <= 16 and value fits in length bits.
    */
    void
    send_bits(int value, int length)
    {
        if(bi_valid_ > (int)Buf_size - length)
        {
            bi_buf_ |= (std::uint16_t)value << bi_valid_;
            put_short(bi_buf_);
            bi_buf_ = (std::uint16_t)value >> (Buf_size - bi_valid_);
            bi_valid_ += length - Buf_size;
        }
        else
        {
            bi_buf_ |= (std::uint16_t)(value) << bi_valid_;
            bi_valid_ += length;
        }
    }

    // Send a code of the given tree
    void
    send_code(int value, ct_data const* tree)
    {
        send_bits(tree[value].fc, tree[value].dl);
    }

    /*  Mapping from a distance to a distance code. dist is the
        distance - 1 and must not have side effects. _dist_code[256]
        and _dist_code[257] are never used.
    */
    std::uint8_t
    d_code(unsigned dist)
    {
        if(dist < 256)
            return lut_.dist_code[dist];
        return lut_.dist_code[256+(dist>>7)];
    }

    /*  Update a hash value with the given input byte
        IN  assertion: all calls to to update_hash are made with
            consecutive input characters, so that a running hash
            key can be computed from the previous key instead of
            complete recalculation each time.
    */
    void
    update_hash(uInt& h, std::uint8_t c)
    {
        h = ((h << hash_shift_) ^ c) & hash_mask_;
    }

    /*  Initialize the hash table (avoiding 64K overflow for 16
        bit systems). prev[] will be initialized on the fly.
    */
    void
    clear_hash()
    {
        head_[hash_size_-1] = 0;
        std::memset((Byte *)head_, 0,
            (unsigned)(hash_size_-1)*sizeof(*head_));
    }

    /*  Compares two subtrees, using the tree depth as tie breaker
        when the subtrees have equal frequency. This minimizes the
        worst case length.
    */
    bool
    smaller(ct_data const* tree, int n, int m)
    {
        return tree[n].fc < tree[m].fc ||
            (tree[n].fc == tree[m].fc &&
                depth_[n] <= depth_[m]);
    }

    /*  Insert string str in the dictionary and set match_head to the
        previous head of the hash chain (the most recent string with
        same hash key). Return the previous length of the hash chain.
        If this file is compiled with -DFASTEST, the compression level
        is forced to 1, and no hash chains are maintained.
        IN  assertion: all calls to to INSERT_STRING are made with
            consecutive input characters and the first minMatch
            bytes of str are valid (except for the last minMatch-1
            bytes of the input file).
    */
    void
    insert_string(IPos& hash_head)
    {
        update_hash(ins_h_, window_[strstart_ + (minMatch-1)]);
        hash_head = prev_[strstart_ & w_mask_] = head_[ins_h_];
        head_[ins_h_] = (std::uint16_t)strstart_;
    }

    //--------------------------------------------------------------------------

    /* Values for max_lazy_match, good_match and max_chain_length, depending on
     * the desired pack level (0..9). The values given below have been tuned to
     * exclude worst case performance for pathological files. Better values may be
     * found for specific files.
     */
    struct config
    {
       std::uint16_t good_length; /* reduce lazy search above this match length */
       std::uint16_t max_lazy;    /* do not perform lazy search above this match length */
       std::uint16_t nice_length; /* quit search above this match length */
       std::uint16_t max_chain;
       compress_func func;

       config(
               std::uint16_t good_length_,
               std::uint16_t max_lazy_,
               std::uint16_t nice_length_,
               std::uint16_t max_chain_,
               compress_func func_)
           : good_length(good_length_)
           , max_lazy(max_lazy_)
           , nice_length(nice_length_)
           , max_chain(max_chain_)
           , func(func_)
       {
       }
    };

    static
    config
    get_config(std::size_t level)
    {
        switch(level)
        {
        //              good lazy nice chain
        case 0: return {  0,   0,   0,    0, &self::deflate_stored}; // store only
        case 1: return {  4,   4,   8,    4, &self::deflate_fast};   // max speed, no lazy matches
        case 2: return {  4,   5,  16,    8, &self::deflate_fast};
        case 3: return {  4,   6,  32,   32, &self::deflate_fast};
        case 4: return {  4,   4,  16,   16, &self::deflate_slow};   // lazy matches
        case 5: return {  8,  16,  32,   32, &self::deflate_slow};
        case 6: return {  8,  16, 128,  128, &self::deflate_slow};
        case 7: return {  8,  32, 128,  256, &self::deflate_slow};
        case 8: return { 32, 128, 258, 1024, &self::deflate_slow};
        default:
        case 9: return { 32, 258, 258, 4096, &self::deflate_slow};    // max compression
        }
    }

    void
    maybe_init()
    {
        if(! inited_)
            init();
    }

    template<class Unsigned>
    static
    Unsigned
    bi_reverse(Unsigned code, unsigned len);

    BOOST_BEAST_DECL
    static
    void
    gen_codes(ct_data *tree, int max_code, std::uint16_t *bl_count);

    BOOST_BEAST_DECL
    static
    lut_type const&
    get_lut();

    BOOST_BEAST_DECL void doReset             (int level, int windowBits, int memLevel, Strategy strategy);
    BOOST_BEAST_DECL void doReset             ();
    BOOST_BEAST_DECL void doClear             ();
    BOOST_BEAST_DECL std::size_t doUpperBound (std::size_t sourceLen) const;
    BOOST_BEAST_DECL void doTune              (int good_length, int max_lazy, int nice_length, int max_chain);
    BOOST_BEAST_DECL void doParams            (z_params& zs, int level, Strategy strategy, error_code& ec);
    BOOST_BEAST_DECL void doWrite             (z_params& zs, boost::optional<Flush> flush, error_code& ec);
    BOOST_BEAST_DECL void doDictionary        (Byte const* dict, uInt dictLength, error_code& ec);
    BOOST_BEAST_DECL void doPrime             (int bits, int value, error_code& ec);
    BOOST_BEAST_DECL void doPending           (unsigned* value, int* bits);

    BOOST_BEAST_DECL void init                ();
    BOOST_BEAST_DECL void lm_init             ();
    BOOST_BEAST_DECL void init_block          ();
    BOOST_BEAST_DECL void pqdownheap          (ct_data const* tree, int k);
    BOOST_BEAST_DECL void pqremove            (ct_data const* tree, int& top);
    BOOST_BEAST_DECL void gen_bitlen          (tree_desc *desc);
    BOOST_BEAST_DECL void build_tree          (tree_desc *desc);
    BOOST_BEAST_DECL void scan_tree           (ct_data *tree, int max_code);
    BOOST_BEAST_DECL void send_tree           (ct_data *tree, int max_code);
    BOOST_BEAST_DECL int  build_bl_tree       ();
    BOOST_BEAST_DECL void send_all_trees      (int lcodes, int dcodes, int blcodes);
    BOOST_BEAST_DECL void compress_block      (ct_data const* ltree, ct_data const* dtree);
    BOOST_BEAST_DECL int  detect_data_type    ();
    BOOST_BEAST_DECL void bi_windup           ();
    BOOST_BEAST_DECL void bi_flush            ();
    BOOST_BEAST_DECL void copy_block          (char *buf, unsigned len, int header);

    BOOST_BEAST_DECL void tr_init             ();
    BOOST_BEAST_DECL void tr_align            ();
    BOOST_BEAST_DECL void tr_flush_bits       ();
    BOOST_BEAST_DECL void tr_stored_block     (char *bu, std::uint32_t stored_len, int last);
    BOOST_BEAST_DECL void tr_tally_dist       (std::uint16_t dist, std::uint8_t len, bool& flush);
    BOOST_BEAST_DECL void tr_tally_lit        (std::uint8_t c, bool& flush);

    BOOST_BEAST_DECL void tr_flush_block      (z_params& zs, char *buf, std::uint32_t stored_len, int last);
    BOOST_BEAST_DECL void fill_window         (z_params& zs);
    BOOST_BEAST_DECL void flush_pending       (z_params& zs);
    BOOST_BEAST_DECL void flush_block         (z_params& zs, bool last);
    BOOST_BEAST_DECL int  read_buf            (z_params& zs, Byte *buf, unsigned size);
    BOOST_BEAST_DECL uInt longest_match       (IPos cur_match);

    BOOST_BEAST_DECL block_state f_stored     (z_params& zs, Flush flush);
    BOOST_BEAST_DECL block_state f_fast       (z_params& zs, Flush flush);
    BOOST_BEAST_DECL block_state f_slow       (z_params& zs, Flush flush);
    BOOST_BEAST_DECL block_state f_rle        (z_params& zs, Flush flush);
    BOOST_BEAST_DECL block_state f_huff       (z_params& zs, Flush flush);

    block_state
    deflate_stored(z_params& zs, Flush flush)
    {
        return f_stored(zs, flush);
    }

    block_state
    deflate_fast(z_params& zs, Flush flush)
    {
        return f_fast(zs, flush);
    }

    block_state
    deflate_slow(z_params& zs, Flush flush)
    {
        return f_slow(zs, flush);
    }

    block_state
    deflate_rle(z_params& zs, Flush flush)
    {
        return f_rle(zs, flush);
    }

    block_state
    deflate_huff(z_params& zs, Flush flush)
    {
        return f_huff(zs, flush);
    }
};

//--------------------------------------------------------------------------

// Reverse the first len bits of a code
template<class Unsigned>
Unsigned
deflate_stream::
bi_reverse(Unsigned code, unsigned len)
{
    BOOST_STATIC_ASSERT(std::is_unsigned<Unsigned>::value);
    BOOST_ASSERT(len <= 8 * sizeof(unsigned));
    Unsigned res = 0;
    do
    {
        res |= code & 1;
        code >>= 1;
        res <<= 1;
    }
    while(--len > 0);
    return res >> 1;
}

} // detail
} // zlib
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/zlib/detail/deflate_stream.ipp>
#endif

#endif

/* deflate_stream.hpp
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
*/