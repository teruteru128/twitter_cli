# cTwitter

## Requirement definition

- Tweet status
- Return length
- Obtain an access token

## How to use(External design)

- `ctw <status>`
    - tweet &lt;status&gt;.
    - If no argument is specified, it reads standard input and tweets it.
- `ctw --register`
    - Register to ctw.
- `ctw --login`
    - Login to ctw
- `ctw --logout`
    - Logout from ctw
- `ctw --init`
    - This may not be used.
    - Create config file(s)?
- `ctw --tweet-length <status>`
    - Returns the length of the status.
    - Alias
        - `ctw -l <status>`
- `ctw --help`
    - Show help.

## TODO

1. Implement command line argument parser
1. Implement setting file argument parser
1. Implement tweeting function
1. Implement authentication function
1. Implement login / logout function

## Contents of setting file

- Consumer key and consumer secret
- Access Token and token secret

## Logics

- コマンドライン引数のパース
- 認可要求の提示からアクセストークン取得までの一連のロジック
- ツイート
- ステータスの長さを返す

## Definition

- 要件定義
- 外部設計
- 内部設計

Config loadConfig
環境変数とか設定ファイルとか読み込んでConfigオブジェクトを返す
void freeConfig
Configオブジェクトを開放する
int createConfigFile
コンフィグファイルを作成する。initコマンドで呼び出される
コンフィグファイル
コンシューマーキーペアとアクセストークンペアを保存するファイル。
initコマンドで設定ファイル作成
設定ファイルにコンシューマーキーとコンシューマーシークレットを設定
registerコマンドでアプリケーション認証してアクセストークンとトークンシークレットを取得、設定ファイルに設定
tweetコマンドでツイート
YAML
TOML
JSON
