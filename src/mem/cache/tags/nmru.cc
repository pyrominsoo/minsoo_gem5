/**
 * @file
 * Definitions of a NMRU tag store.
 */

#include "mem/cache/tags/nmru.hh"

#include "base/random.hh"
#include "debug/CacheRepl.hh"
#include "mem/cache/base.hh"

NMRU::NMRU(const Params *p)
    : BaseSetAssoc(p)
{
}

BaseSetAssoc::BlkType*
NMRU::accessBlock(Addr addr, bool is_secure, Cycles &lat)
{
    // Accesses are based on parent class, no need to do anything special
    BlkType *blk = BaseSetAssoc::accessBlock(addr, is_secure, lat);

    if (blk != NULL) {
        // move this block to head of the MRU list
        sets[blk->set].moveToHead(blk);
        DPRINTF(CacheRepl, "set %x: moving blk %x (%s) to MRU\n",
                blk->set, regenerateBlkAddr(blk->tag, blk->set),
                is_secure ? "s" : "ns");
    }

    return blk;
}

BaseSetAssoc::BlkType*
NMRU::findVictim(Addr addr)
{
    BlkType *blk = BaseSetAssoc::findVictim(addr);

    // if all blocks are valid, pick a replacement that is not MRU at random
    if (blk->isValid()) {
        // find a random index within the bounds of the set
        int idx = random_mt.random<int>(1, assoc - 1);
        assert(idx < assoc);
        assert(idx >= 0);
        blk = sets[extractSet(addr)].blks[idx];

        DPRINTF(CacheRepl, "set %x: selecting blk %x for replacement\n",
                blk->set, regenerateBlkAddr(blk->tag, blk->set));
    }

    return blk;
}

void
NMRU::insertBlock(PacketPtr pkt, BlkType *blk)
{
    BaseSetAssoc::insertBlock(pkt, blk);

    int set = extractSet(pkt->getAddr());
    sets[set].moveToHead(blk);
}

void
NMRU::invalidate(BlkType *blk)
{
    BaseSetAssoc::invalidate(blk);

    // should be evicted before valid blocks
    int set = blk->set;
    sets[set].moveToTail(blk);
}

NMRU*
NMRUParams::create()
{
    return new NMRU(this);
}

