/*
 * Title: ProvisionRoleWildcardAceHandler file.
 * Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
 * Version: 2
 * Date: September 15, 2023
 *
 * Intellectual Property:
 * Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
 *
 * License:
 * This file is owned by Terrortronics / Bradley Elenbaas.
 * This file observes the IoTivity License.
 */

package org.iotivity.onboardingtool;

import android.util.Log;
import android.widget.Toast;

import org.iotivity.OCObtDeviceStatusHandler;
import org.iotivity.OCUuid;
import org.iotivity.OCUuidUtil;

public class ProvisionRoleWildcardAceHandler implements OCObtDeviceStatusHandler {

    private static final String TAG = ProvisionRoleWildcardAceHandler.class.getSimpleName();

    private OnBoardingActivity activity;

    public ProvisionRoleWildcardAceHandler(OnBoardingActivity activity) {
        this.activity = activity;
    }

    @Override
    public void handler(OCUuid uuid, int status) {
        String deviceId = OCUuidUtil.uuidToString(uuid);

        final String msg = (status >= 0) ?
                "Successfully provisioned role * ACE on device " + deviceId :
                "Error provisioning role * ACE on device " + deviceId + ", status = " + status;

        Log.d(TAG, msg);
        activity.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(activity, msg, Toast.LENGTH_LONG).show();
            }
        });
    }
}
