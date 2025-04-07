
plugins {
    alias(libs.plugins.androidApplication)
}

android {
    signingConfigs {
        create("release") {
            storeFile = file("../../Materials/Publish/android-key.jks")
            storePassword = "pass"
            keyPassword = "pass"
            keyAlias = "grom"
        }
    }
    namespace = "com.grom.template"
    compileSdk = 34

/*    androidResources {
        noCompress.add("assets.pak")
    }*/

    sourceSets.getByName("main") {
        assets.srcDirs("../../assets")
    }

    defaultConfig {
        applicationId = "com.grom.template"
        minSdk = 23
        targetSdk = 34
        versionCode = 1
        versionName = "1.0.0.beta.1"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags += "-std=c++17"
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
            signingConfig = signingConfigs.getByName("release")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    buildFeatures {
        prefab = true
    }
    externalNativeBuild {
        cmake {
            path = file("../../CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

dependencies {

    //implementation(libs.gms.play.services.ads)
    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.games.activity)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)

}