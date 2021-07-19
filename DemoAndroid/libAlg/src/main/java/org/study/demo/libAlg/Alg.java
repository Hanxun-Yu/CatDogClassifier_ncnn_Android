package org.study.demo.libAlg;

import android.content.Context;

import org.study.demo.libAlg.util.AssetsUtil;

import java.io.File;

/**
 * author: wsyuhx
 * created on: 2021/7/15 18:43
 * description:
 */
public class Alg {
    Jni jni = new Jni();

    public void init(Context context) {
        String modelFoldName = "model";
        String rootPath = context.getObbDir().getPath();

        if (!new File(rootPath + File.separator + modelFoldName).exists()) {
            AssetsUtil.copy(context, modelFoldName, rootPath);
        }
        jni.init(rootPath + File.separator + modelFoldName + File.separator + "180.bin",
                rootPath + File.separator + modelFoldName + File.separator + "180.param");
    }

    public float process(byte[] data, int w, int h) {
        return jni.process(data, w, h);
    }
}
