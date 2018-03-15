/*
 * Copyright (c) 2017-2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: Implements public API for pmo to interact with target/WMI
 */

#include "wlan_pmo_tgt_api.h"
#include "wlan_pmo_hw_filter_public_struct.h"
#include "wlan_pmo_obj_mgmt_public_struct.h"
#include "wlan_pmo_main.h"

QDF_STATUS pmo_tgt_conf_hw_filter(struct wlan_objmgr_psoc *psoc,
				  struct pmo_hw_filter_params *req)
{
	QDF_STATUS status;
	struct wlan_pmo_tx_ops ops;

	pmo_enter();

	pmo_debug("Configure hw filter; vdev_id:%u, mode:%d",
		  req->vdev_id, req->mode);

	ops = GET_PMO_TX_OPS_FROM_PSOC(psoc);
	if (!ops.send_conf_hw_filter_req) {
		pmo_err("send_conf_hw_filter_req is null");
		status = QDF_STATUS_E_NULL_VALUE;
		goto exit_with_status;
	}

	status = ops.send_conf_hw_filter_req(psoc, req);

exit_with_status:
	pmo_exit();

	return status;
}

