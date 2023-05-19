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

以下のように、TurtleBot3用のUnityプロジェクトへ移動します。

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

Unityエディタ起動後、プロジェクトビューの　`Scenes/TB3/TB3Work` をダブルクリックしてください。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/84b25820-83ce-4f87-b45d-aab57bc299dd)

奥のほうに `TurtleBot3` が見えると思います。

そのまま、`Window/Hakoniwa/Generate` をクリックして終了です。


