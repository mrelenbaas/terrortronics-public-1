/*
 * Title: ObtInitHandler file.
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

import org.iotivity.OCMainInitHandler;
import org.iotivity.oc.OcDevice;
import org.iotivity.oc.OcPlatform;

public class ObtInitHandler implements OCMainInitHandler {

    private static final String TAG = ObtInitHandler.class.getSimpleName();

    private OnBoardingActivity activity;
    private OcPlatform obtPlatform;

    public ObtInitHandler(OnBoardingActivity activity, OcPlatform obtPlatform) {
        this.activity = activity;
        this.obtPlatform = obtPlatform;
    }

    @Override
    public int initialize() {
        Log.d(TAG, "inside ObtInitHandler.initialize()");
        int ret = obtPlatform.platformInit("OCF");
        if (ret >= 0) {
            OcDevice device = new OcDevice("/oic/d", "oic.d.dots", "OBT", "ocf.2.0.5", "ocf.res.1.0.0,ocf.sh.1.0.0");
            ret |= obtPlatform.addDevice(device);
            // Note: device must be added to platform before additional resource types can be added
            device.bindResourceType("oic.d.ams");
            device.bindResourceType("oic.d.cms");
        }

        return ret;
    }

    @Override
    public void registerResources() {
        Log.d(TAG, "inside ObtInitHandler.registerResources()");
    }

    @Override
    public void requestEntry() {
        Log.d(TAG, "inside ObtInitHandler.requestEntry()");
    }
}
