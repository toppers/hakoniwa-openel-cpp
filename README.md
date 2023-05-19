# hakoniwa-openel-cpp

# 前提環境

## Unity

* Unity Hub
  * Unity Hub 3.4.1
* Unity
  * Unity 2021.3.7f1

なお、Unityおよび Unity Hub はインストールされていることを前提として解説します。

# Windows環境
* Windows10 Home, Windows 11
* WSL2/WSLg/Ubuntu20.0.4
* WSL2/Docker Engine

# インストール方法

OpenEL箱庭用のリポジトリを以下のようにクローンします。

```
git clone --recursive git@github.com:toppers/hakoniwa-openel-cpp.git
```

クローンぐ終わったら、以下のようにディレクトリ移動します。

```
cd hakoniwa-openel-cpp/
```

## docker イメージの取得

```
bash runtime/docker/pull-image.bash 
```

成功するとこうなります。

```
$ docker images
REPOSITORY                              TAG       IMAGE ID       CREATED        SIZE
toppersjp/hakoniwa-openel-runtime-tb3   v1.0.0    11e5b4f27de2   3 hours ago    3.83GB
```

次に、OpenELのサンプルコードをビルドします。

```
bash runtime/docker/run.bash build
```
