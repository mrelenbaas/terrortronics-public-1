/*
 * Title: ProvisionCertificateHandler file.
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

import org.iotivity.OCObtStatusHandler;

public class ProvisionIdCertificateHandler implements OCObtStatusHandler {

    private static final String TAG = ProvisionIdCertificateHandler.class.getSimpleName();

    private OnBoardingActivity activity;

    public ProvisionIdCertificateHandler(OnBoardingActivity activity) {
        this.activity = activity;
    }

    @Override
    public void handler(int status) {
        final String msg = (status >= 0) ?
                "Successfully provisioned identity certificate" :
                "Error provisioning identity certificate, status = " + status;

        Log.d(TAG, msg);
        activity.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(activity, msg, Toast.LENGTH_LONG).show();
            }
        });
    }
}
