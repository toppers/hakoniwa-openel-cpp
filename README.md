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
REPOSITORY                              TAG       IMAGE ID       CREATED         SIZE
toppersjp/hakoniwa-openel-runtime-tb3   v1.0.0    6c8e32e9719e   4 minutes ago   3.83GB
```

## OpenELサンプルコードのビルド

次に、OpenELのサンプルコードをビルドします。

```
bash runtime/docker/run.bash build
```

成功すると、以下のように、`hako-openel`　という実行バイナリが出来上がります。

```
$ ls sample/tb3model/cmake-build/hako-openel 
sample/tb3model/cmake-build/hako-openel
```

## Unity プロジェクトのインストール

まず最初に、Unity用のコンフィグファイルを配置します。

```
cp runtime/workspace/config/hakoniwa_path.json hakoniwa-unity-tb3model/plugin/plugin-srcs/hakoniwa_path.json
```

次に、TurtleBot3用のUnityプロジェクトへ移動します。

```
cd hakoniwa-unity-tb3model/
```

そして、必要なUnityモジュール類をインストールします。

```
 bash install.bash 
```

成功すると、`DONE`というメッセージが出ますので、この状態で Unity Hub で当該プロジェクトを開きましょう。

対象フォルダ：`hakoniwa-unity-tb3model\plugin\plugin-srcs`

成功するとこうなります。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/2712f400-ffef-4294-a9a5-4ccbdc407740)

なお、Unityエディタのバージョンによっては、起動中にエラーとなる場合があります。
その場合、途中、ダイアログがポップアップされて警告されますが、気にせず起動しましょう。

原因は、`Newtonsoft.Json` が不足しているためです。
対応方法は、下記記事にある通り、Unityのパッケージマネージャから `Newtonsoft.Json`をインストールすることで解消できます。

https://qiita.com/sakano/items/6fa16af5ceab2617fc0f

## TurtleBot3の配置

Unityエディタ起動後、プロジェクトビューの　`Scenes/Hakoniwa` をダブルクリックしてください。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/e36c2057-2d57-483f-8546-3a53fe21692d)

お気づきかもしれませんが、インストール直後は TurtleBot3 は存在していません。
代わりに、`SampleRobo`が配置されています。

これを `TurtleBot3` に差し替えましょう。

まず、ヒエラルキービューの `Robot` 配下に、`SampleRobot` が見えると思います。これを削除しましょう。
対象のオブジェクトを選択して、右クリックして `Delete` を押下することで削除できます。

次に、プロジェクトビューの　`Prefab/Robots` をクリックすると下のほうに `TB3RoboModel` があります。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/d43d7b7e-bb90-4450-a724-0f978655047d)

これをドラッグして、ヒエラルキービューの `Robot` の下でドロップします。成功するとこうなります。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/25ef1784-367d-41c0-bf59-734d67428a20)

この状態ですと、床に埋まっていますので、ロボットの位置調整をしてあげましょう。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/0aef7fa3-57d1-4223-803e-cf64cbea495c)

※緑の矢印（Y軸）をクリックしたまま上に移動させるだけです。

最後に、`Window/Hakoniwa/Generate` をクリックして終了です。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/8be12b93-48d8-4fee-bac0-4e02ca0e6a9d)

この `Generate`の操作は、Windowsを再起動した場合は必ず１回は実行してください。

## シミュレーション実行方法

本リポジトリのトップディレクトリに移動します。

```
cd hakoniwa-openel-cpp/
```

以下のコマンドで箱庭のランタイムおよび OpenELのサンプルプログラムを起動します。

```
 bash runtime/docker/run.bash run
```

起動ログ：
```
INFO: ACTIVATING MOSQUITTO
[ 4550.932676]~DLT~    7~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...
INFO: ACTIVATING HAKO-MASTER
OPEN RECIEVER UDP PORT=172.26.207.137:54001
OPEN SENDER UDP PORT=172.26.207.137:54002
mqtt_url=mqtt://172.26.207.137:1883
PUBLISHER Connecting to the MQTT server...
PUBLISHER CONNECTED to the MQTT server...
delta_msec = 20
max_delay_msec = 100
INFO: shmget() key=255 size=80768
Server Start: 172.26.207.137:50051
INFO: TB3RoboModel create_lchannel: logical_id=0 real_id=0 size=48
hako_pdu_write_init(0, 48) ret=1
ActuatorHako::fncInit()
OpenEL Motor L init OK
ActuatorHako::fncInit()
OpenEL Motor R init OK
SensorHako::fncInit()
OpenEL Sensor init OK
```

この状態で、Unityの再生ボタンをクリックします。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/21ed5a97-bfaf-4c24-beca-ef676e4c66e3)

このように、TB3が見えると思いますので、`START`ボタンをクリックするとシミュレーション開始します。


シミュレーション終了する場合は、Unityの再生ボタンを止めて、起動していた WSL2のターミナルを　`CTRL+C` で停止してください。


# デモ

https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/d45dc53a-5f25-428a-9ea6-eacc727f5da3




