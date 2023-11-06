/*
 * Title: OcfDeviceInfo file.
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

import org.iotivity.OCUuid;

public class OcfDeviceInfo {

    private OCUuid uuid;
    private String name;

    OcfDeviceInfo(OCUuid uuid, String name) {
        this.uuid = uuid;
        this.name = name;
    }

    public OCUuid getUuid() {
        return uuid;
    }

    public String getName() {
        return name;
    }

    public int hashCode() {
        int result = 17;
        result = 37 * result + uuid.hashCode();
        result = 37 * result + name.hashCode();
        return result;
    }

    public boolean equals(Object obj) {
        OcfDeviceInfo other = (OcfDeviceInfo) obj;
        return (uuid.equals(other.uuid) && name.equals(other.name));
    }
}
