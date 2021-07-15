package org.study.demo.libAlg.util;

import android.content.Context;
import android.content.res.AssetManager;
import android.text.TextUtils;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class AssetsUtil {
    private static final String TAG = "AssetsUtil";

    /**
     * copy assets to releaseDir with full path
     *
     * @param context
     * @param assetsDir
     * @param targetParentDir
     * @author brian
     */
    public static void copy(Context context, String assetsDir,
                                     String targetParentDir) {

        Log.d(TAG,"copy src:"+assetsDir+" tar:"+targetParentDir);

        if (TextUtils.isEmpty(targetParentDir)) {
            return;
        } else if (targetParentDir.endsWith("/")) {
            targetParentDir = targetParentDir.substring(0, targetParentDir.length() - 1);
        }

        if (TextUtils.isEmpty(assetsDir) || assetsDir.equals("/")) {
            assetsDir = "";
        } else if (assetsDir.endsWith("/")) {
            assetsDir = assetsDir.substring(0, assetsDir.length() - 1);
        }

        AssetManager assets = context.getAssets();
        try {
            String[] fileNames = assets.list(assetsDir);//只能获取到文件(夹)名,所以还得判断是文件夹还是文件
            if (fileNames.length > 0) {// is dir
                new File(targetParentDir+"/"+assetsDir).mkdirs();
                for (String name : fileNames) {
                    if (!TextUtils.isEmpty(assetsDir)) {
                        name = assetsDir + "/" + name;//补全assets资源路径
                    }
                    Log.i(TAG, "name:" + name);
                    String[] childNames = assets.list(name);//判断是文件还是文件夹
                    if (!TextUtils.isEmpty(name) && childNames.length > 0) {
                        copy(context, name, targetParentDir);//递归, 因为资源都是带着全路径,
                        //所以不需要在递归是设置目标文件夹的路径
                    } else {
                        InputStream is = assets.open(name);
                        String target = targetParentDir + "/" + name;
                        Log.d(TAG,"doCopy src:"+name+" tar:"+target);
                        copyAndClose(is, new FileOutputStream(target));
                    }
                }
            } else {// is file
                InputStream is = assets.open(assetsDir);
                String target = targetParentDir + "/" + assetsDir;

                // 写入文件前, 需要提前级联创建好路径, 下面有代码贴出
                copyAndClose(is, new FileOutputStream(target));
                Log.d(TAG,"doCopy src:"+assetsDir+" tar:"+target);

            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void closeQuietly(OutputStream out) {
        try {
            if (out != null) out.close();
            ;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private static void closeQuietly(InputStream is) {
        try {
            if (is != null) {
                is.close();
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private static void copyAndClose(InputStream is, OutputStream out) throws IOException {
        copy(is, out);
        closeQuietly(is);
        closeQuietly(out);
    }

    private static void copy(InputStream is, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int n = 0;
        while (-1 != (n = is.read(buffer))) {
            out.write(buffer, 0, n);
        }
    }

}