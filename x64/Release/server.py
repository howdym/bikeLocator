from bottle import Bottle, route, run, static_file

app = Bottle()

@app.route('/static/<filename>')
def server_static(filename):
    return static_file(filename, root="./")

run(app, host='localhost', port=8080)
