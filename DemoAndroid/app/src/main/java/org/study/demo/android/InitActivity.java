package org.study.demo.android;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;


/**
 * Created by wsyuhx
 * 2020/12/23
 * description:
 */
public class InitActivity extends AppCompatActivity {
    final String TAG = getClass().getSimpleName();
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (checkPermission())
            init();
    }



    private void init() {
        startMain();
        finish();
    }

    private void startMain() {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }

    final int REQUEST_CODE = 99;
    String[] permissions = {
            Manifest.permission.CAMERA,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
//            Manifest.permission.RECORD_AUDIO,
    };

    private boolean checkPermission() {
        if(Build.VERSION.SDK_INT < Build.VERSION_CODES.M)
            return true;
        //如果返回true表示已经授权了
        if (
//                checkSelfPermission(Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED
//                &&
        checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
//                && checkSelfPermission(Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED
                ) {
            return true;
        } else {
            // 类似 startActivityForResult()中的REQUEST_CODE
            // 权限列表,将要申请的权限以数组的形式提交。
            // 系统会依次进行弹窗提示。
            // 注意：如果AndroidManifest.xml中没有进行权限声明，这里配置了也是无效的，不会有弹窗提示。

            ActivityCompat.requestPermissions(this,
                    permissions,
                    REQUEST_CODE);
            return false;
        }

    }

    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[], int[] grantResults) {
        switch (requestCode) {
            case REQUEST_CODE: {
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    if (checkPermission())
                        init();
                    // 权限同意了，做相应处理
                } else {
                    if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    || ActivityCompat.shouldShowRequestPermissionRationale(this,
                            Manifest.permission.CAMERA)) {
                        // 用户拒绝过这个权限了，应该提示用户，为什么需要这个权限。
                    }
                }
            }
            return;
        }
    }
}
