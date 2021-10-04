/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _DP_MON_2_0_H_
#define _DP_MON_2_0_H_

#if !defined(DISABLE_MON_CONFIG)
#include <qdf_lock.h>
#include <dp_types.h>

/**
 * struct dp_mon_desc
 *
 * @buf_addr: virtual address
 * @paddr: physical address
 * @in_use: desc is in use
 * @unmapped: used to mark desc an unmapped if the corresponding
 * nbuf is already unmapped
 * @cookie: unique desc identifier
 */
struct dp_mon_desc {
	uint8_t *buf_addr;
	qdf_dma_addr_t paddr;
	uint8_t in_use:1,
		unmapped:1;
	uint32_t cookie;
};

/**
 * struct dp_mon_desc_list_elem_t
 * @next: Next pointer to form free list
 * @mon_desc: DP mon descriptor
 */
union dp_mon_desc_list_elem_t {
	union dp_mon_desc_list_elem_t *next;
	struct dp_mon_desc mon_desc;
};

/**
 * struct dp_mon_desc_pool - monitor desc pool
 * @pool_size: number of descriptor in the pool
 * @array: pointer to array of descriptor
 * @freelist: pointer to free descriptor list
 * @lock: Protection for the descriptor pool
 * @owner: owner for nbuf
 * @buf_size: Buffer size
 * @buf_alignment: Buffer alignment
 */
struct dp_mon_desc_pool {
	uint32_t pool_size;
	union dp_mon_desc_list_elem_t *array;
	union dp_mon_desc_list_elem_t *freelist;
	qdf_spinlock_t lock;
	uint8_t owner;
	uint16_t buf_size;
	uint8_t buf_alignment;
};

/**
 * struct dp_mon_pdev_be - BE specific monitor pdev object
 * @mon_pdev: monitor pdev structure
 */
struct dp_mon_pdev_be {
	struct dp_mon_pdev mon_pdev;
};

/**
 * struct dp_mon_soc_be - BE specific monitor soc
 * @mon_soc: Monitor soc structure
 * @tx_mon_buf_ring: TxMon replenish ring
 * @tx_mon_dst_ring: TxMon Destination ring
 * @tx_desc_mon: descriptor pool for tx mon src ring
 * @rx_desc_mon: descriptor pool for rx mon src ring
 * @rx_mon_ring_fill_level: rx mon ring refill level
 * @tx_mon_ring_fill_level: tx mon ring refill level
 */
struct dp_mon_soc_be {
	struct dp_mon_soc mon_soc;
	/* Source ring for Tx monitor */
	struct dp_srng tx_mon_buf_ring;
	struct dp_srng tx_mon_dst_ring[MAX_NUM_LMAC_HW];

	/* Sw descriptor pool for tx mon source ring */
	struct dp_mon_desc_pool tx_desc_mon;
	/* Sw descriptor pool for rx mon source ring */
	struct dp_mon_desc_pool rx_desc_mon;

	uint16_t rx_mon_ring_fill_level;
	uint16_t tx_mon_ring_fill_level;
};
#endif

#endif /* _DP_MON_2_0_H_ */
